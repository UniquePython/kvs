#ifndef STORENODE_H_
#define STORENODE_H_

#include "entry.h"
#include "kvs/type.h"

typedef struct StoreNode
{
    Entry entry;
    struct StoreNode *next;

} StoreNode;

bool StoreNodeCreate(KvsType key, KvsType value, StoreNode **out);
void StoreNodeDestroy(StoreNode **ptr);

#endif
