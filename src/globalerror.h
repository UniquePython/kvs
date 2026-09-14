#ifndef GLOBALERROR_H_
#define GLOBALERROR_H_

#include "kvs/globalerror.h"

extern KvsGEC gec;
extern char *gem;

void SetGlobalError(KvsGEC code, const char *fmt, ...);

#endif
