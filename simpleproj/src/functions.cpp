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
	for (;;)
	{
	  int *ptmpval = new int;
	  *ptmpval = i++%100000;
	  para->prollq->Push(ptmpval);
	  usleep(10);
	}
	return p;
}

void *ThreadPop(void *p)
{
	queuepara *para = (queuepara*)p;
	int i = 0;
	int tmpval = 0;
  
	for (;;)
	{
	  int *pint = (int *)para->prollq->Pop();
	  if (pint != NULL)
	    {
	      printf("pop thread seq[%d] pop value:%d\n", para->iqnum, *pint);
	      delete pint;
	    }
	  sleep(2);
	}
	return p;
}
