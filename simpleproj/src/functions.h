#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "../../basestruct/heads.h"
#include "../../ZW/basefun/basefun.h"
#include <unistd.h>
#include <sys/types.h>

const char *swap(int *a, int *b);

void DealIPFile();

void *ThreadAdd(void *p);
void *ThreadStatic(void *p);
void Test();
#endif
