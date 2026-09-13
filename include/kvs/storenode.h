#ifndef KVS_STORENODE_H_
#define KVS_STORENODE_H_

#include "kvs/entry.h"
#include <stddef.h>

typedef struct StoreNode
{
    Entry entry;
    struct StoreNode *next;

} StoreNode;

#endif
