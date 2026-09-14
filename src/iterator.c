#include "kvs/iterator.h"
#include "iterator.h"
#include "memory.h"

bool KvsIterCreate(const Store *store, KvsIterator **out)
{
    if (store == NULL || out == NULL)
        return false;

    KvsIterator *it;

    if (!Allocate(sizeof(KvsIterator), &it))
        return false;

    it->current = store;

    *out = it;
    return true;
}

bool KvsIterNext(KvsIterator *it, Type *key, Type *value)
{
    if (it == NULL || key == NULL || value == NULL)
        return false;

    if (it->current == NULL)
        return false;

    *key = it->current->entry.key;
    *value = it->current->entry.value;
    it->current = it->current->next;

    return true;
}

void KvsIterDestroy(KvsIterator **ptr)
{
    Release(ptr);
}
