#ifndef ROLLQUEUE_H
#define ROLLQUEUE_H
#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define QUEUE_SIZE 10000

typedef struct queueELEM
{
  void *pelem;
}QELEM;

class RollQueue;

struct queuepara
{
	int iqnum;
	RollQueue *prollq;
};

class RollQueue
{
  pthread_mutex_t *pLock;
  void *ppQueue[QUEUE_SIZE];
  int iCur; //current pos
  int iSize; //size of this queue
  int iCount;
  int iEnd;  
 public:
  RollQueue();
  ~RollQueue();
  bool Push(void *pElem);
  void *Pop();
};

#endif
