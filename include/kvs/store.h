#ifndef KVS_STORE_H_
#define KVS_STORE_H_

#include "kvs/storenode.h"
#include <stddef.h>

typedef struct
{
    StoreNode *head;
    size_t size;

} Store;

#endif
