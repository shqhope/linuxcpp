#include "functions.h"

const char *swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
	return __FILE__;
}

void queen()
{
  int bb = 0;
  static int cc = 100;
}

void *ThreadPush(void *p)
{
	queuepara *para = (queuepara*)p;
	int i = 0;
	int tmpval = 0;
	for (;;)
	{
		tmpval = i++%100000;
		para->prollq->Push(&tmpval);
		usleep(10);
	}
	return p;
}

void *ThreadPop(void *p)
{
	for (;;)
	{

	}
	return p;
}
