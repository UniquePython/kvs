#ifndef KVS_TYPEKIND_H_
#define KVS_TYPEKIND_H_

// clang-format off
typedef enum
{
    TK_U8  = 1,
    TK_U16 = 2,
    TK_U32 = 3,
    TK_U64 = 4,

} KvsTypeKind;
// clang-format on

const char *KvsTypeKindName(KvsTypeKind kind);

#endif
