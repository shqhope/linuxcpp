#include "src/functions.h"
#include "../basestruct/linklist.h"
#include "../basestruct/tree.h"
#include "../basestruct/queen.h"
#include "../zw/basefun/basefun.h"
#include "../apue/char01/char01.h"
#include "../zw/logger/oriloger.h"
#include "../apue/char02/char02.h"

int main(int argc, const char **argv)
{
/*	BaseFun::test();
	int iFile = open("./main.cpp", O_RDONLY);
	char buf[512] = {0};
	if (iFile != -1)
	{
		read(iFile, buf, 511);
		close(iFile);
	}
	cout<< "hello world"<<endl;
	printf("hello world\n");
	int a = 100,b = 200;
	cout << swap(&a, &b) << endl;

	vector<string> vecArr;
	BaseFun::GetFileArray("/home/sq/github/linuxcpp/APUE", vecArr, ".cpp", true);
	for (vector<string>::iterator itor=vecArr.begin(); itor!=vecArr.end();++itor)
	{
		cout<<"filename:"<<itor->c_str()<<endl;
	}
	//LinkList::test();
	//BTree::run();
	//RollQueue::test();
	return 0;
 */
	//testRollQueue();
//	OriLoger::WriteLog("wo le ge ca %s", "bbb");


//	cout<<"change some words"<<endl;
//	//LinkList::testSort0();
//	const char *pWords = "hello xiaoming \nnihaoma \nhow do you do\n";
//	char *buffWords = new char[1024];
//	memcpy(buffWords, pWords, strlen(pWords));
//	char *pline = NULL;
//	while ((pline = BaseFun::SplitLineForBlock(buffWords, '\n')) != NULL)
//	{
//		cout<<pline<<endl;
//	}
//	Test();
//	char01::test();
//	char02::test();
//	char buffline[1024] = {0};
//	memcpy(buffline, "hello \tworld\tdo\t'''heheo\t000\t\[]\n", 1000);
//	const char *pcols[10];
//	int icols = BaseFun::SplitLine(buffline, '\t', pcols, 10);
//	int icols2 = BaseFun::SplitLine(NULL, '\t', pcols, 10);
	BaseFun::testThread();

	return 0;
}
