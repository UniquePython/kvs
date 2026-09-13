#include "kvs/type.h"

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
