#ifndef KVS_STOREERROR_H_
#define KVS_STOREERROR_H_

#include "kvs/store.h"

typedef enum
{
    KVS_SEC_NO_ERROR,
    KVS_SEC_ITER_ALLOC_FAILED,
    KVS_SEC_NODE_ALLOC_FAILED,

} KvsStoreErrorCode;

typedef KvsStoreErrorCode KvsSEC;

KvsSEC KvsGetStoreErrorCode(const KvsStore *store);
const char *KvsGetStoreErrorMsg(const KvsStore *store);

#endif
