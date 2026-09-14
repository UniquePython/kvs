#include "kvs/type.h"
#include <inttypes.h>

KvsType KvsTypeU8(uint8_t value)
{
    return (KvsType){
        .kind = TK_U8,
        .as.u8.data = value,
    };
}

KvsType KvsTypeU16(uint16_t value)
{
    return (KvsType){
        .kind = TK_U16,
        .as.u16.data = value,
    };
}

KvsType KvsTypeU32(uint32_t value)
{
    return (KvsType){
        .kind = TK_U32,
        .as.u32.data = value,
    };
}

KvsType KvsTypeU64(uint64_t value)
{
    return (KvsType){
        .kind = TK_U64,
        .as.u64.data = value,
    };
}

bool KvsTypeEquals(KvsType a, KvsType b)
{
    if (a.kind != b.kind)
        return false;

    switch (a.kind)
    {
    case TK_U8:
        return a.as.u8.data == b.as.u8.data;

    case TK_U16:
        return a.as.u16.data == b.as.u16.data;

    case TK_U32:
        return a.as.u32.data == b.as.u32.data;

    case TK_U64:
        return a.as.u64.data == b.as.u64.data;

    default:
        return false;
    }
}

#define U8_FMT "%" PRIu8
#define U16_FMT "%" PRIu16
#define U32_FMT "%" PRIu32
#define U64_FMT "%" PRIu64

bool KvsTypePrint(KvsType type, FILE *stream)
{
    if (stream == NULL)
        return false;

    if (fprintf(stream, "%s: ", KvsTypeKindName(type.kind)) < 0)
        return false;

    switch (type.kind)
    {
    case TK_U8:
        return fprintf(stream, U8_FMT, type.as.u8.data) >= 0;
    case TK_U16:
        return fprintf(stream, U16_FMT, type.as.u16.data) >= 0;
    case TK_U32:
        return fprintf(stream, U32_FMT, type.as.u32.data) >= 0;
    case TK_U64:
        return fprintf(stream, U64_FMT, type.as.u64.data) >= 0;
    default:
        return false;
    }
}
