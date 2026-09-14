#include "kvs/iterator.h"
#include "iterator.h"
#include "store.h"
#include "memory.h"

bool KvsIterCreate(const KvsStore *store, KvsIterator **out)
{
    if (store == NULL || out == NULL)
        return false;

    KvsIterator *it;

    if (!Allocate(sizeof(KvsIterator), &it))
        return false;

    it->current = store->head;

    *out = it;
    return true;
}

bool KvsIterNext(KvsIterator *it, KvsType *key, KvsType *value)
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

bool KvsForEach(const KvsStore *store, KvsForEachFn fn, void *ctx)
{
    if (store == NULL || fn == NULL)
        return false;

    KvsIterator *it;
    if (!KvsIterCreate(store, &it))
        return false;

    KvsType key, value;
    while (KvsIterNext(it, &key, &value))
        fn(key, value, ctx);

    KvsIterDestroy(&it);
    return true;
}
