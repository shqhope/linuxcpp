#include "rollqueue.h"

RollQueue::RollQueue()
{
  iCur=0;
  iEnd=0;
  iCount=0;
  iSize=QUEUE_SIZE;
  pLock = new pthread_mutex_t;
  pthread_mutex_init(pLock, 0);
}

RollQueue::~RollQueue()
{
  pthread_mutex_destroy(pLock);
  delete pLock;
}

bool RollQueue::Push(void *pElem)
{
  pthread_mutex_lock(pLock);
  if (iCount < iSize)
    {
      ppQueue[iCur]=pElem;
      iCur=iCur++%iSize;
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

void *RollQueue::Pop()
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
      iEnd=iEnd++%iSize;
      pthread_mutex_unlock(pLock);
      return ppQueue[iTmp];
    }      
}
