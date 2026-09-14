#ifndef KVS_STOREERROR_H_
#define KVS_STOREERROR_H_

#include "kvs/store.h"

typedef enum
{
    KVS_SEC_NO_ERROR,

} KvsStoreErrorCode;

typedef KvsStoreErrorCode KvsSEC;

KvsSEC KvsGetStoreErrorCode(const KvsStore *store);
const char *KvsGetStoreErrorMsg(const KvsStore *store);

#endif
