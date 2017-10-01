#ifndef LINKLIST_H
#define LINKLIST_H
#include "heads.h"
#include <stdio.h>
#include <string.h>

#define LINKBLKSZ 1024
#define BLOCKSZ 4*1024*1024

struct LNode
{
	char *pelem;
	struct LNode *pNext;
};

struct BufBlk
{
	char *pblk;
	BufBlk *pnext;
};

class LinkList
{
private:
	LNode *m_pHead;
	LNode *m_pTail;
	int m_iCount;
	int m_iIdxLeft;
	BufBlk *m_pBlk;
	BufBlk *m_pCurBlk;
	int m_iBlkpos;
public:
	LinkList(int count = 0);
	~LinkList();

public:
	LNode *PushBack(const char *pstr);
	//
	LNode *GetIdxBlk(int idxsize = LINKBLKSZ);
	LNode *PushBack_DyAllocIdx(const char *pstr);
	//
	char *GetBuff(const int buflen);
	LNode *PushBack_DyAllocIdxBlk(const char *pstr);

public:
	static void test();
};

#endif
