#include "kvs/type.h"
#include <inttypes.h>

bool TypeEquals(Type a, Type b)
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

bool TypePrint(Type type, FILE *stream)
{
    if (stream == NULL)
        return false;

    if (fprintf(stream, "%s: ", TypeKindName(type.kind)) < 0)
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
