#ifndef KVS_ITERATOR_H_
#define KVS_ITERATOR_H_

#include "kvs/store.h"
#include "kvs/type.h"

typedef struct KvsIterator KvsIterator;

bool KvsIterCreate(const Store *store, KvsIterator **out);
bool KvsIterNext(KvsIterator *it, Type *key, Type *value);
void KvsIterDestroy(KvsIterator **ptr);

typedef void (*KvsForEachFn)(Type key, Type value, void *ctx);
bool KvsForEach(const Store *store, KvsForEachFn fn, void *ctx);

// Note: mutating the store while an iterator over it is live is
// undefined behavior. The caller is responsible for not doing that.

#endif
