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
#include <stdio.h>

using namespace std;


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
//	Queen *queen = new Queen;
//	queen->Init(5);
//	queen->printQ();
//	queen->GetFrame(0);
	return 0;
  */

	RollQueue *pqueue = new RollQueue;
	queuepara qpapush;
	qpapush.iqnum = 0;
	qpapush.prollq = pqueue;
  pthread_t thread0;
  int iRet = pthread_create(&thread0, NULL, ThreadPush, &qpapush);
  if (iRet != 0)
  {
	  cout<<"error while create thread"<<endl;
	  exit(0);
  }

  queuepara arrqpara[10];
  for (int i = 0; i < 10; ++i)
  {
	  arrqpara[i].iqnum = i;
	  arrqpara[i].prollq = new RollQueue;
	  pthread_t thread1;
	  pthread_create(&thread1, NULL, ThreadPop, arrqpara+i);
	  if (iRet != 0)
	  {
		  cout<<"error while create pop thread"<<endl;
		  exit(0);
	  }
  }
  return 0;
}
