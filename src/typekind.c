#include "kvs/typekind.h"

const char *KvsTypeKindName(KvsTypeKind kind)
{
    switch (kind)
    {
    case KVS_TK_U8:
        return "u8";
    case KVS_TK_U16:
        return "u16";
    case KVS_TK_U32:
        return "u32";
    case KVS_TK_U64:
        return "u64";
    default:
        return "unknown";
    }
}
