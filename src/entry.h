#ifndef ENTRY_H_
#define ENTRY_H_

#include "kvs/entry.h"
#include "kvs/type.h"

struct Entry
{
    Type key;
    Type value;
};

#endif
