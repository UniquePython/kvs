#ifndef KVS_STOREERROR_H_
#define KVS_STOREERROR_H_

#include "kvs/store.h"

typedef enum
{
    KVS_SEC_NO_ERROR,
    KVS_SEC_ITER_ALLOC_FAILED,
    KVS_SEC_NODE_ALLOC_FAILED,
    KVS_SEC_TMP_PATH_ALLOC_FAILED,
    KVS_SEC_TMP_FILE_OPEN_FAILED,
    KVS_SEC_WRITE_FAILED,
    KVS_SEC_CLOSE_FAILED,
    KVS_SEC_RENAME_FAILED,
    KVS_SEC_CORRUPTED_DATA,

} KvsStoreErrorCode;

typedef KvsStoreErrorCode KvsSEC;

KvsSEC KvsGetStoreErrorCode(const KvsStore *store);
const char *KvsGetStoreErrorMsg(const KvsStore *store);

#endif
