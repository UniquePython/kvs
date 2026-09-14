#include "kvs/persist.h"
#include "kvs/iterator.h"
#include "kvs/type.h"
#include "kvs/store.h"
#include "memory.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

static const unsigned char KVS_MAGIC[4] = {'K', 'V', 'S', '\0'};
static const uint8_t KVS_FORMAT_VERSION = 1;

static void WriteBE16(uint8_t out[2], uint16_t value)
{
    out[0] = (uint8_t)(value >> 8);
    out[1] = (uint8_t)(value);
}

static void WriteBE32(uint8_t out[4], uint32_t value)
{
    out[0] = (uint8_t)(value >> 24);
    out[1] = (uint8_t)(value >> 16);
    out[2] = (uint8_t)(value >> 8);
    out[3] = (uint8_t)(value);
}

static void WriteBE64(uint8_t out[8], uint64_t value)
{
    out[0] = (uint8_t)(value >> 56);
    out[1] = (uint8_t)(value >> 48);
    out[2] = (uint8_t)(value >> 40);
    out[3] = (uint8_t)(value >> 32);
    out[4] = (uint8_t)(value >> 24);
    out[5] = (uint8_t)(value >> 16);
    out[6] = (uint8_t)(value >> 8);
    out[7] = (uint8_t)(value);
}

static bool WriteKvsType(FILE *stream, KvsType type)
{
    uint8_t kindByte = (uint8_t)type.kind;
    if (fwrite(&kindByte, sizeof(kindByte), 1, stream) != 1)
        return false;

    switch (type.kind)
    {
    case KVS_TK_U8:
        return fwrite(&type.as.u8.data, sizeof(type.as.u8.data), 1, stream) == 1;

    case KVS_TK_U16:
    {
        uint8_t buf[2];
        WriteBE16(buf, type.as.u16.data);
        return fwrite(buf, sizeof(buf), 1, stream) == 1;
    }

    case KVS_TK_U32:
    {
        uint8_t buf[4];
        WriteBE32(buf, type.as.u32.data);
        return fwrite(buf, sizeof(buf), 1, stream) == 1;
    }

    case KVS_TK_U64:
    {
        uint8_t buf[8];
        WriteBE64(buf, type.as.u64.data);
        return fwrite(buf, sizeof(buf), 1, stream) == 1;
    }

    default:
        return false;
    }
}

static uint16_t ReadBE16(const uint8_t in[2])
{
    return (uint16_t)((uint16_t)(in[0] << 8) | in[1]);
}

static uint32_t ReadBE32(const uint8_t in[4])
{
    return ((uint32_t)in[0] << 24) | ((uint32_t)in[1] << 16) |
           ((uint32_t)in[2] << 8) | (uint32_t)in[3];
}

static uint64_t ReadBE64(const uint8_t in[8])
{
    return ((uint64_t)in[0] << 56) | ((uint64_t)in[1] << 48) |
           ((uint64_t)in[2] << 40) | ((uint64_t)in[3] << 32) |
           ((uint64_t)in[4] << 24) | ((uint64_t)in[5] << 16) |
           ((uint64_t)in[6] << 8) | (uint64_t)in[7];
}

static bool ReadKvsType(FILE *stream, KvsType *out, bool *corrupted)
{
    if (corrupted != NULL)
        *corrupted = false;

    uint8_t kindByte;
    if (fread(&kindByte, sizeof(kindByte), 1, stream) != 1)
        return false; // clean EOF at entry boundary — corrupted stays false

    switch ((KvsTypeKind)kindByte)
    {
    case KVS_TK_U8:
    {
        uint8_t value;
        if (fread(&value, sizeof(value), 1, stream) != 1)
        {
            if (corrupted != NULL)
                *corrupted = true;
            return false;
        }
        *out = KvsTypeU8(value);
        return true;
    }
    case KVS_TK_U16:
    {
        uint8_t buf[2];
        if (fread(buf, sizeof(buf), 1, stream) != 1)
        {
            if (corrupted != NULL)
                *corrupted = true;
            return false;
        }
        *out = KvsTypeU16(ReadBE16(buf));
        return true;
    }
    case KVS_TK_U32:
    {
        uint8_t buf[4];
        if (fread(buf, sizeof(buf), 1, stream) != 1)
        {
            if (corrupted != NULL)
                *corrupted = true;
            return false;
        }
        *out = KvsTypeU32(ReadBE32(buf));
        return true;
    }
    case KVS_TK_U64:
    {
        uint8_t buf[8];
        if (fread(buf, sizeof(buf), 1, stream) != 1)
        {
            if (corrupted != NULL)
                *corrupted = true;
            return false;
        }
        *out = KvsTypeU64(ReadBE64(buf));
        return true;
    }
    default:
        if (corrupted != NULL)
            *corrupted = true;
        return false;
    }
}

bool KvsSave(const KvsStore *store, const char *path)
{
    if (store == NULL || path == NULL)
        return false;

    size_t pathLen = strlen(path);
    size_t tmpLen = pathLen + 4 + 1; // ".tmp" + null terminator

    char *tmpPath;
    if (!Allocate(tmpLen, &tmpPath))
        return false;

    memcpy(tmpPath, path, pathLen);
    memcpy(tmpPath + pathLen, ".tmp", 5);

    FILE *stream = fopen(tmpPath, "wb");
    if (stream == NULL)
    {
        Release(&tmpPath);
        return false;
    }

    bool ok = true;

    if (ok && fwrite(KVS_MAGIC, sizeof(KVS_MAGIC), 1, stream) != 1)
        ok = false;

    if (ok && fwrite(&KVS_FORMAT_VERSION, sizeof(KVS_FORMAT_VERSION), 1, stream) != 1)
        ok = false;

    if (ok)
    {
        KvsIterator *it;
        if (!KvsIterCreate(store, &it))
        {
            ok = false;
        }
        else
        {
            KvsType key, value;
            while (ok && KvsIterNext(it, &key, &value))
            {
                if (!WriteKvsType(stream, key) || !WriteKvsType(stream, value))
                    ok = false;
            }
            KvsIterDestroy(&it);
        }
    }

    if (fclose(stream) != 0)
        ok = false;

    if (ok && rename(tmpPath, path) != 0)
        ok = false;

    if (!ok)
        remove(tmpPath); // best-effort cleanup; ignore failure here, we're already reporting failure

    Release(&tmpPath);
    return ok;
}

bool KvsLoad(const char *path, KvsStore **out)
{
    if (path == NULL || out == NULL)
        return false;

    FILE *stream = fopen(path, "rb");
    if (stream == NULL)
        return false;

    unsigned char magic[4];
    if (fread(magic, sizeof(magic), 1, stream) != 1 ||
        memcmp(magic, KVS_MAGIC, sizeof(magic)) != 0)
    {
        fclose(stream);
        return false;
    }

    uint8_t formatVersion;
    if (fread(&formatVersion, sizeof(formatVersion), 1, stream) != 1 ||
        formatVersion != KVS_FORMAT_VERSION)
    {
        fclose(stream);
        return false;
    }

    KvsStore *store;
    if (!KvsCreate(&store))
    {
        fclose(stream);
        return false;
    }

    bool ok = true;
    while (ok)
    {
        KvsType key;
        bool corrupted;
        if (!ReadKvsType(stream, &key, &corrupted))
        {
            if (corrupted)
                ok = false;
            break; // clean EOF: no more entries, stop normally
        }

        KvsType value;
        if (!ReadKvsType(stream, &value, &corrupted))
        {
            ok = false; // a key without a matching value is always corruption,
            break;      // never a valid stopping point
        }

        if (!KvsSet(store, key, value))
        {
            ok = false;
            break;
        }
    }

    fclose(stream);

    if (!ok)
    {
        KvsDestroy(&store);
        return false;
    }

    *out = store;
    return true;
}
