#ifndef ROLLQUEUE_H
#define ROLLQUEUE_H

#define QUEUE_SIZE 1000

typedef struct queueELEM
{
  void *pelem;
}QELEM;

class RollQueue
{
  void **ppQueue[QUEUE_SIZE];
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
