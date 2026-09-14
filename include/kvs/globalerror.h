#ifndef KVS_GLOBALERROR_H_
#define KVS_GLOBALERROR_H_

typedef enum
{
    KVS_GEC_NO_ERROR,
    KVS_GEC_WRITE_FAILED,
    KVS_GEC_STORE_ALLOC_FAILED,
    KVS_GEC_FILE_OPEN_FAILED,
    KVS_GEC_BAD_MAGIC,
    KVS_GEC_UNSUPPORTED_VERSION,

} KvsGlobalErrorCode;

typedef KvsGlobalErrorCode KvsGEC;

KvsGEC KvsGetGlobalErrorCode(void);
const char *KvsGetGlobalErrorMsg(void);

#endif
