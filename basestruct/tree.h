#ifndef TREE_H
#define TREE_H
#include "heads.h"

struct TNode
{
	int key;
	char *elem;
	TNode *lch;
	TNode *rch;
};

/**
 * @brief The BTree class
 * 二叉平衡树
 */
class BTree
{
private:
	TNode *m_pRoot;
	int m_iLvNum;
	int m_iElemCount;
private:
	void *mergeTree();
	static TNode *createTree0(int *arr, int arrsz, int &pos);
public:
	void CreateTree(int *arr, int arrsz);
	TNode *InsertNode();
	TNode *SearchKey(int key, int &findcount);

	static void run();
};



#endif
