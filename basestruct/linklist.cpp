#include "linklist.h"

LinkList::LinkList(int isize)
{
	m_pTail = m_pHead = new LNode;
	m_iCount = 0;
	m_iIdxLeft = 0;
	m_pCurBlk = m_pBlk = NULL;
}

LinkList::~LinkList()
{

}

bool DelKey(const char *pstr)
{

}

/**
 * @brief LinkList::PushBack 在链表的最后插入元素
 * @param pstr
 * @return
 */
LNode* LinkList::PushBack(const char *pstr)
{
	if (pstr != NULL)
	{
		LNode *ptmp = new LNode;
		ptmp->pNext = NULL;
		int istrlen = strlen(pstr);
		ptmp->pelem = new char[istrlen + 1];
		strcpy(ptmp->pelem, pstr);
		ptmp->pelem[istrlen] = '\0';
		m_pTail->pNext = ptmp;
		m_pTail = m_pTail->pNext;
		return m_pTail;
	}
	else
	{
		return NULL;
	}
}

LNode *LinkList::GetIdxBlk(int idxsize /*= IDXBLKSZ*/)
{
	if (m_iIdxLeft < 1)
	{
		LNode *ptmp = new LNode[idxsize];
		m_iIdxLeft = idxsize;
		return ptmp;
	}
	else
	{
		return m_pTail+1;
	}
}

/**
 * @brief LinkList::PushBack_DyAllocIdx
 * @param pstr
 * @return
 * linklist block mode
 * 预先分配链表空间方式
 */
LNode* LinkList::PushBack_DyAllocIdx(const char *pstr)
{
	if (pstr != NULL)
	{
		LNode *ptmp = GetIdxBlk();
		ptmp->pNext = NULL;
		int istrlen = strlen(pstr);
		ptmp->pelem = new char[istrlen + 1];
		strcpy(ptmp->pelem, pstr);
		ptmp->pelem[istrlen] = '\0';
		m_pTail->pNext = ptmp;
		m_iIdxLeft--;
		m_pTail = m_pTail->pNext;
		return m_pTail;
	}
	else
	{
		return NULL;
	}
}

char *LinkList::GetBuff(const int buflen)
{
	if (m_pCurBlk == NULL || m_iBlkpos + buflen > BLOCKSZ)
	{
		BufBlk *tmpBlk = new BufBlk;
		tmpBlk->pblk = new char[BLOCKSZ];
		tmpBlk->pnext = NULL;
		m_iBlkpos = 0;
		if (m_pCurBlk != NULL)
		{
			m_pCurBlk->pnext = tmpBlk;
		}
		m_pCurBlk = tmpBlk;
		return tmpBlk->pblk;
	}
	else
	{
		return m_pCurBlk->pblk + m_iBlkpos;
	}
}

/**
 * @brief LinkList::PushBack_DyAllocIdxBlk
 * @param pstr
 * @return
 * dynamic manage idx and buff BLOCK
 */
LNode* LinkList::PushBack_DyAllocIdxBlk(const char *pstr)
{
	if (pstr != NULL)
	{
		LNode *ptmp = GetIdxBlk();
		ptmp->pNext = NULL;
		int istrlen = strlen(pstr);
		ptmp->pelem = GetBuff(istrlen + 1);
		strcpy(ptmp->pelem, pstr);
		ptmp->pelem[istrlen] = '\0';
		m_pTail->pNext = ptmp;
		m_iIdxLeft--;
		m_pTail = m_pTail->pNext;
		return m_pTail;
	}
	else
	{
		return NULL;
	}
}

//////////////////测试代码////////////////////
/// \brief LinkList::test
/// 测试三种内存方式的效率
///
///

const char *teststrs[] =
{
	"hello world",
	"string2",
	"trible kill",
	"glod like"
};

int iteststr = sizeof(teststrs)/sizeof(teststrs[0]);

/**
 * @brief LinkList::test
 */
void LinkList::test()
{
	int iTotal = 10000000;

	struct timeval tmval;
	struct timezone tmzone;
	gettimeofday(&tmval, &tmzone);
	long int begtm = ((tmval.tv_sec%100)*1000000)+tmval.tv_usec;
	printf("beg %ld\n", begtm);
	LinkList *linklist = new LinkList;
	for (int i = 0; i < iTotal; ++i)
	{
		linklist->PushBack(teststrs[i%iteststr]);
	}
	gettimeofday(&tmval, &tmzone);
	int endtm = ((tmval.tv_sec%100)*1000000)+tmval.tv_usec;
	printf("end %d\nspendtm: %ld\n", endtm, endtm - begtm);

	printf("beg %ld\n", begtm);
	LinkList *linklist2 = new LinkList;
	for (int i = 0; i < iTotal; ++i)
	{
		linklist2->PushBack_DyAllocIdx(teststrs[i%iteststr]);
	}
	gettimeofday(&tmval, &tmzone);
	endtm = ((tmval.tv_sec%100)*1000000)+tmval.tv_usec;
	printf("end %d\nspendtm: %ld\n", endtm, endtm - begtm);

	printf("beg %ld\n", begtm);
	LinkList *linklist3 = new LinkList;
	for (int i = 0; i < iTotal; ++i)
	{
		linklist3->PushBack_DyAllocIdxBlk(teststrs[i%iteststr]);
	}
	gettimeofday(&tmval, &tmzone);
	endtm = ((tmval.tv_sec%100)*1000000)+tmval.tv_usec;
	printf("end %d\nspendtm: %ld\n", endtm, endtm - begtm);

	return ;
}

void Prn(const LNode *pnode)
{
	///打印生成的链表
	if (pnode == NULL)
		return;
	for (const LNode *p = pnode->pNext; p!= NULL; p=p->pNext)
	{
		printf("pval:%3d\n", p->iNum);
	}
}

/**
 * @brief 插入排序
 * @param head
 */
void Sort_Insert(LNode *head)
{
	///排序算法
	for (LNode *p = head->pNext; p->pNext != NULL; )
	{
		LNode *q = p->pNext;
		if (q->iNum < p->iNum)
		{
			LNode *qq = head;
			for (; qq != p; qq=qq->pNext)
			{
				if (q->iNum < qq->pNext->iNum)
				{
					break;
				}
			}
			p->pNext = p->pNext->pNext;
			q->pNext = qq->pNext;
			qq->pNext = q;
		}
		else
		{
			p=p->pNext;
		}
	}
}

void LinkList::testSort0()
{
	int ilen = 10;
	LNode *pnode = new LNode[ilen];
	srand(1);
	for (int i = 0; i < ilen; ++i)
	{
		(pnode+i)->iNum = rand()%100;
		(pnode+i)->pNext = (pnode+i+1);
	}
	(pnode+ilen-1)->pNext = NULL;
	///做个头节点
	LNode *head = new LNode;
	head->pNext = pnode;
	Prn(head);
	///插入排序
	Sort_Insert(head);
	printf("sorted seq:\n");
	Prn(head);
}

