#include "kvs/globalerror.h"
#include "globalerror.h"
#include "memory.h"
#include <stdarg.h>
#include <stdio.h>

KvsGEC gec = KGEC_NO_ERROR;
char *gem = NULL;

void SetGlobalError(KvsGEC code, const char *fmt, ...)
{
    Release(&gem);

    if (fmt == NULL)
    {
        gec = code;
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
        gem = NULL;
        gec = code;
        return;
    }

    char *buf;
    if (!Allocate((size_t)len + 1, &buf))
    {
        va_end(argsCopy);
        gem = NULL;
        gec = code; // code is left as given; a NULL message next to a
                    // non-KGEC_NO_ERROR code just means the message
                    // itself couldn't be allocated
        return;
    }

    vsnprintf(buf, (size_t)len + 1, fmt, argsCopy);
    va_end(argsCopy);

    gem = buf;
    gec = code;
}

KvsGEC KvsGetGlobalErrorCode(void)
{
    return gec;
}

const char *KvsGetGlobalErrorMsg(void)
{
    return gem;
}
