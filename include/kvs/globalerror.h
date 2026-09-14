#ifndef KVS_GLOBALERROR_H_
#define KVS_GLOBALERROR_H_

typedef enum
{
    KGEC_NO_ERROR,

} KvsGlobalErrorCode;

typedef KvsGlobalErrorCode KvsGEC;

KvsGEC KvsGetGlobalErrorCode(void);
char *KvsGetGlobalErrorMsg(void);

#endif
