#include <iostream>
#include "src/functions.h"
#include "../basestruct/linklist.h"
#include "../basestruct/tree.h"
#include "../basestruct/queen.h"

using namespace std;

int main(int argc, const char **argv)
{
	cout<< "hello world"<<endl;
	int a = 100,b = 200;
	cout << swap(&a, &b) << endl;
	//LinkList::test();
	//BTree::run();
	Queen *queen = new Queen;
	queen->Init(5);
	queen->printQ();
	int iframe = 0;
	queen->GetFrame(0, iframe);
	return 0;
}
