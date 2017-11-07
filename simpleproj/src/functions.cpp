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

///测试原子操作和锁的效率
//volatile
unsigned long ulStatic = 0;
volatile int atom;
pthread_rwlock_t *plock;

void *ThreadAdd(void *p)
{
	int *pi = (int *)p;
	unsigned long istatic;
	for (;;)
	{
		if (*pi == 0)
		{
			__sync_fetch_and_add(&atom, 1);
			while (atom != 1)
			{
				__sync_fetch_and_sub(&atom, 1);
				usleep(1);
				__sync_fetch_and_add(&atom, 1);
			}
			ulStatic ++;
			__sync_fetch_and_sub(&atom, 1);
		}
		else
		{
			pthread_rwlock_wrlock(plock);
			ulStatic++;
			pthread_rwlock_unlock(plock);
		}
		usleep(1);
	}
}
void *ThreadStatic(void *p)
{
	int *pi = (int *)p;
	unsigned long istatic;
	for (;;)
	{
		if (*pi == 0)
		{
			__sync_fetch_and_add(&atom, 1);
			while (atom != 1)
			{
				__sync_fetch_and_sub(&atom, 1);
				usleep(300);
				__sync_fetch_and_add(&atom, 1);
			}
			istatic = ulStatic;
			__sync_fetch_and_sub(&atom, 1);
		}
		else
		{
			pthread_rwlock_rdlock(plock);
			istatic = ulStatic;
			pthread_rwlock_unlock(plock);
		}
		printf("static val: %ld\n", istatic);
		sleep(2);
	}
}

void Test()
{
	plock = new pthread_rwlock_t;
	pthread_rwlock_init(plock,0);
	atom = 0;
	
	int mode = 0;
	pthread_t thread0;
	int iRet = pthread_create(&thread0, NULL, ThreadStatic,  &mode);
	if (iRet != 0)
	{
		puts("error thread0");
		exit(0);
	}
	
	for (int i = 0; i < 300; ++i)
	{
		iRet = pthread_create(&thread0, NULL, ThreadAdd,  &mode);
		if (iRet != 0)
		{
			printf("error thread1  %d", i);
			exit(0);
		}
	}
	
	for(;;)
	{
		sleep(2);
	}
	
}
