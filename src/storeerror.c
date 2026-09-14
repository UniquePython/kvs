#include "storeerror.h"
#include "memory.h"
#include <stdarg.h>
#include <stdio.h>

void SetStoreError(KvsStore *store, KvsSEC code, const char *fmt, ...)
{
    if (store == NULL)
        return;

    Release(&store->error.msg);

    if (fmt == NULL)
    {
        store->error.code = code;
        return;
    }

    va_list args;
    va_start(args, fmt);

    va_list argsCopy;
    va_copy(argsCopy, args);
    int len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    if (len < 0)
    {
        va_end(argsCopy);
        store->error.msg = NULL;
        store->error.code = code;
        return;
    }

    char *buf;
    if (!Allocate((size_t)len + 1, &buf))
    {
        va_end(argsCopy);
        store->error.msg = NULL;
        store->error.code = code; // code is left as given; a NULL message next to a
                                  // non-KSEC_NO_ERROR code just means the message
                                  // itself couldn't be allocated
        return;
    }

    vsnprintf(buf, (size_t)len + 1, fmt, argsCopy);
    va_end(argsCopy);

    store->error.msg = buf;
    store->error.code = code;
}

KvsSEC KvsGetStoreErrorCode(const KvsStore *store)
{
    if (store == NULL)
        return KSEC_NO_ERROR;

    return store->error.code;
}

const char *KvsGetStoreErrorMsg(const KvsStore *store)
{
    if (store == NULL)
        return NULL;

    return store->error.msg;
}
