#ifndef KVS_ITERATOR_H_
#define KVS_ITERATOR_H_

#include "kvs/store.h"
#include "kvs/type.h"

typedef struct KvsIterator KvsIterator;

bool KvsIterCreate(const KvsStore *store, KvsIterator **out);
bool KvsIterNext(KvsIterator *it, KvsType *key, KvsType *value);
void KvsIterDestroy(KvsIterator **ptr);

typedef void (*KvsForEachFn)(KvsType key, KvsType value, void *ctx);
bool KvsForEach(const KvsStore *store, KvsForEachFn fn, void *ctx);

// Note: mutating the store while an iterator over it is live is
// undefined behavior. The caller is responsible for not doing that.

#endif
