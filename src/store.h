#ifndef STORE_H_
#define STORE_H_

#include "kvs/store.h"
#include "kvs/storeerror.h"
#include "storenode.h"
#include <stddef.h>

struct KvsStore
{
    StoreNode *head;
    size_t size;

    struct
    {
        KvsSEC code;
        char *msg;

    } error;
};

#endif
