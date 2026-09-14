#ifndef STORE_H_
#define STORE_H_

#include "kvs/store.h"
#include "storenode.h"
#include <stddef.h>

struct KvsStore
{
    StoreNode *head;
    size_t size;
};

#endif
