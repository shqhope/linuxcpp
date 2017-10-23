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

bool RollQueue::Push(void *pElem)
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
      iEnd=(iEnd+1)%iSize;
      iCount--;
      void *pRet = ppQueue[iTmp]; 
      pthread_mutex_unlock(pLock);
      return pRet;
    }      
}
