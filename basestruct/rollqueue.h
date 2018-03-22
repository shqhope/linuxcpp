#ifndef ROLLQUEUE_H
#define ROLLQUEUE_H
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "heads.h"

#define QUEUE_SIZE 10000

typedef struct queueELEM
{
	void *pelem;
	//***用于扩展，添加其他属性或处理方法
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
	static void *ThreadPush(void *p);
	static void *ThreadPop(void *p);

public:
	RollQueue();
	~RollQueue();
	bool QPush(void *pElem);
	void *QPop();
	static void test();
};



#endif
