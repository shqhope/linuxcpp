#include "functions.h"

const char *swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
	return __FILE__;
}

void queen()
{
  int bb = 0;
  static int cc = 100;
}

void DealIPFile()
{
	char buffLine[1024];
	FILE *pfile = NULL;
	if ((pfile = fopen("../TESTDATA/手机归属地数据库-13、14、15、18号段--移动、联通、电信.txt", "r"))!=NULL)	//test1d 的上一层
	{
		int iline = 0;
		while(fgets(buffLine, 1023, pfile) != NULL)
		{
			if (iline % 100==0)
				sleep(5);
			buffLine[strlen(buffLine)-1] = '\0';
			cout<<buffLine<<"\tline : "<< iline++ <<endl;
		}
		fclose(pfile);
	}
}
