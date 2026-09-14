#ifndef KVS_STORE_H_
#define KVS_STORE_H_

#include "kvs/type.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct KvsStore KvsStore;

bool KvsCreate(KvsStore **out);
void KvsDestroy(KvsStore **ptr);

bool KvsSize(const KvsStore *store, size_t *size);

bool KvsHas(const KvsStore *store, KvsType key);
bool KvsGet(const KvsStore *store, KvsType key, KvsType *value);

bool KvsSet(KvsStore *store, KvsType key, KvsType value);
bool KvsSetOverwrote(KvsStore *store, KvsType key, KvsType value, bool *yes);

bool KvsDelete(KvsStore *store, KvsType key);

#endif
