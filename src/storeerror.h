#ifndef STOREERROR_H_
#define STOREERROR_H_

#include "kvs/storeerror.h"
#include "store.h"

void SetStoreError(KvsStore *store, KvsSEC code, const char *fmt, ...);

#endif
