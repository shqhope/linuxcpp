#include "rollqueue.h"

RollQueue::RollQueue()
{
	iCur=0;
	iEnd=0;
	iCount=0;
	iSize=QUEUE_SIZE;
	memset(ppQueue, 0, sizeof(void *)*QUEUE_SIZE);
	pLock = new pthread_mutex_t;
	pthread_mutex_init(pLock, 0);
}

RollQueue::~RollQueue()
{
	pthread_mutex_destroy(pLock);
	delete pLock;
}

bool RollQueue::QPush(void *pElem)
{
  pthread_mutex_lock(pLock);
  if (iCount < iSize)
    {
      ppQueue[iCur]=pElem;
      iCur=(iCur+1)%iSize;
      iCount++;
      pthread_mutex_unlock(pLock);
      return true;
    }
  else
    {
      pthread_mutex_unlock(pLock);
      return false;
    }
}

void *RollQueue::QPop()
{
  pthread_mutex_lock(pLock);
  if (iCount < 1)
    {
      pthread_mutex_unlock(pLock);
      return NULL;
    }
  else
    {
      int iTmp = iEnd;
      iEnd=(iEnd+1)%iSize;
      iCount--;
      void *pRet = ppQueue[iTmp]; 
      pthread_mutex_unlock(pLock);
      return pRet;
    }      
}


/**
   test codes
 */
void *RollQueue::ThreadPush(void *p)
{
	queuepara *para = (queuepara*)p;
	int i = 0;
	for (;;)
	{
	  int *ptmpval = new int;
	  *ptmpval = i++%100000;
	  para->prollq->QPush(ptmpval);
	  usleep(10);
	}
	return p;
}

void *RollQueue::ThreadPop(void *p)
{
	queuepara *para = (queuepara*)p;
	int i = 0;
	int tmpval = 0;
  
	for (;;)
	{
	  int *pint = (int *)para->prollq->QPop();
	  if (pint != NULL)
	    {
	      printf("pop thread seq[%d] pop value:%d\n", para->iqnum, *pint);
	      delete pint;
	    }
	  sleep(2);
	}
	return p;
}

void RollQueue::test()
{
	cout<<"start testrollqueue"<<endl;
	RollQueue *pqueue = new RollQueue;
	queuepara qpapush;
	qpapush.iqnum = 0;
	qpapush.prollq = pqueue;
	pthread_t thread0;
	int iRet = pthread_create(&thread0, NULL, ThreadPush, &qpapush);
	if (iRet != 0)
	{
		cout<<"error while create thread"<<endl;
		exit(0);
	}

  queuepara arrqpara[10];
  for (int i = 0; i < 10; ++i)
  {
	  arrqpara[i].iqnum = i;
	  arrqpara[i].prollq = pqueue;
	  pthread_t thread1;
	  pthread_create(&thread1, NULL, ThreadPop, arrqpara+i);
	  if (iRet != 0)
	  {
		  cout<<"error while create pop thread"<<endl;
		  exit(0);
	  }
  }
  time_t tm_print;
  for (;;)
    {
      if (time(0) - tm_print > 10)
	{
	  printf("print tm:%ld qsize:%d\n", time(0), 0);
	  tm_print=time(0);
	}
	  sleep(2);
    }

}
