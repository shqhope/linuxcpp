#include <iostream>
#include "src/functions.h"
#include "../basestruct/linklist.h"
#include "../basestruct/tree.h"
#include "../basestruct/queen.h"
#include "../ZW/basefun/basefun.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main(int argc, const char **argv)
{
	BaseFun::test();
	int iFile = open("./main.cpp", O_RDONLY);
	char buf[512] = {0};
	if (iFile != -1)
	{
		read(iFile, buf, 511);
		close(iFile);
	}
	cout<< "hello world"<<endl;
	int a = 100,b = 200;
	cout << swap(&a, &b) << endl;
	//LinkList::test();
	//BTree::run();
//	Queen *queen = new Queen;
//	queen->Init(5);
//	queen->printQ();
//	queen->GetFrame(0);
	return 0;
}
