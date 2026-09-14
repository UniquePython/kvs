#ifndef ENTRY_H_
#define ENTRY_H_

#include "kvs/type.h"

typedef struct
{
    KvsType key;
    KvsType value;

} Entry;

#endif
