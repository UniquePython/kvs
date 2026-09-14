#ifndef KVS_GLOBALERROR_H_
#define KVS_GLOBALERROR_H_

typedef enum
{
    KVS_GEC_NO_ERROR,
    KVS_GEC_WRITE_FAILED,
    KVS_GEC_STORE_ALLOC_FAILED,

} KvsGlobalErrorCode;

typedef KvsGlobalErrorCode KvsGEC;

KvsGEC KvsGetGlobalErrorCode(void);
const char *KvsGetGlobalErrorMsg(void);

#endif
