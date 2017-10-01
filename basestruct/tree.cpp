#include "tree.h"

int glbarr[] = {
	1,2,4,8,0,0,9,0,0,5,10,0,0,11,0,0,3,6,12,0,0,13,0,0,7,14,0,0,15,0,0
};

int iglbarrsz = sizeof(glbarr)/sizeof(glbarr[0]);

void *BTree::mergeTree()
{

}

TNode *BTree::createTree0(int *arr, int arrsz, int &pos)
{
	if (arr[pos] == 0 || pos >= arrsz)
	{
		return NULL;
	}
	TNode *tmp = new TNode;
	tmp->key = arr[pos];
	pos++;
	tmp->lch = createTree0(arr, arrsz, pos);
	pos++;
	tmp->rch = createTree0(arr, arrsz, pos);
	return tmp;
}

void BTree::CreateTree(int *arr, int arrpos)
{
	int istart = 0;
	m_pRoot = createTree0(arr, arrpos, istart);
}

TNode *BTree::InsertNode()
{

}

TNode *BTree::SearchKey(int key, int &findcount)
{

}

void BTree::run()
{
	BTree bt;
	bt.CreateTree(glbarr, iglbarrsz);


}

