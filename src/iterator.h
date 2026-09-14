#ifndef ITERATOR_H_
#define ITERATOR_H_

#include "kvs/iterator.h"
#include "storenode.h"

struct KvsIterator
{
    const StoreNode *current;
};

#endif
