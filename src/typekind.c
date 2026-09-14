#include "kvs/typekind.h"

const char *TypeKindName(TypeKind kind)
{
    switch (kind)
    {
    case TK_U8:
        return "u8";
    case TK_U16:
        return "u16";
    case TK_U32:
        return "u32";
    case TK_U64:
        return "u64";
    default:
        return "unknown";
    }
}
