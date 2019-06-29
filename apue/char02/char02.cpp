#include "char02.h"

char02::char02()
{

}

void char02::fun1()
{
	FILE *fp = setmntent("/etc/mtab", "r");
	if (fp != NULL)
	{
		struct mntent buffmnt;
		char buffline[1024];
		while(getmntent_r(fp, &buffmnt, buffline, 1024) != NULL)
		{
			struct statfs buffstatfs;
			statfs(buffmnt.mnt_dir, &buffstatfs);
			printf("Hello [%s] size [%ld]\n", buffmnt.mnt_dir, buffstatfs.f_bsize*buffstatfs.f_frsize);
		}

		endmntent(fp);
	}
}

void char02::test()
{
	fun1();
}
