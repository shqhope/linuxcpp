#include "char04.h"

char04::char04()
{

}

/**
 * @brief char04::ProcWriteOneLine
 * @param p
 * @return
 * 文件操作append动作时，允许多线程写文件
 */
void *char04::ProcWriteOneLine(void *p)
{
	FILE *fp = fopen("/sdzw/test.txt", "a");
	if (fp != NULL)
	{
		fprintf(fp, "Hello world\n");
	}
}

bool char04::Start10Threads()
{

}

void char04::test()
{

}
