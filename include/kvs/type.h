#ifndef KVS_TYPE_H_
#define KVS_TYPE_H_

#include "kvs/typekind.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct
{
    TypeKind kind;

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

} Type;

Type TypeU8(uint8_t value);
Type TypeU16(uint16_t value);
Type TypeU32(uint32_t value);
Type TypeU64(uint64_t value);

bool TypeEquals(Type a, Type b);
bool TypePrint(Type type, FILE *stream);

#endif
