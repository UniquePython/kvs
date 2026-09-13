#ifndef KVS_TYPE_H_
#define KVS_TYPE_H_

#include "kvs/typekind.h"
#include <stdint.h>

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

#endif
