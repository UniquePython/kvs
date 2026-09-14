#ifndef KVS_TYPE_H_
#define KVS_TYPE_H_

#include "kvs/typekind.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct
{
    KvsTypeKind kind;

    union
    {
        struct
        {
            uint8_t data;
        } u8;

        struct
        {
            uint16_t data;
        } u16;

        struct
        {
            uint32_t data;
        } u32;

        struct
        {
            uint64_t data;
        } u64;

    } as;

} KvsType;

KvsType KvsTypeU8(uint8_t value);
KvsType KvsTypeU16(uint16_t value);
KvsType KvsTypeU32(uint32_t value);
KvsType KvsTypeU64(uint64_t value);

bool KvsTypeEquals(KvsType a, KvsType b);
bool KvsTypePrint(KvsType type, FILE *stream);

#endif
