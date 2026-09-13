#ifndef STORENODE_H_
#define STORENODE_H_

#include "entry.h"

typedef struct StoreNode
{
    Entry entry;
    struct StoreNode *next;

} StoreNode;

#endif
