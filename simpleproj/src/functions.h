#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "../../basestruct/heads.h"
#include <unistd.h>

const char *swap(int *a, int *b);

void *ThreadPush(void *p);
void *ThreadPop(void *p);

#endif
