#ifndef KVS_TYPEKIND_H_
#define KVS_TYPEKIND_H_

// clang-format off
typedef enum
{
    KVS_TK_U8  = 1,
    KVS_TK_U16 = 2,
    KVS_TK_U32 = 3,
    KVS_TK_U64 = 4,

} KvsTypeKind;
// clang-format on

const char *KvsTypeKindName(KvsTypeKind kind);

#endif
