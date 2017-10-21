#include rollqueue.h

RollQueue::RollQueue()
{
  iCur=0;
  iEnd=0;
  iCount=0;
  iSize=QUEUE_SIZE;
}

RollQueue::~RollQueue()
{
}

bool RollQueue::Push(void *pElem)
{
  if (iCount < iSize)
    {
      ppQueue[iCur]=pElem;
      iCur=iCur++%iSize;
      iCount++;
      return true;
    }
  else
    {
      return false;
    }
}

void *RollQueue::Pop()
{
  if (iCount < 1)
    {
      return NULL;
    }
  else
    {
      int iTmp = iEnd;
      iEnd=iEnd++%iSize;
      return ppQueue[iTmp];
    }      
}
