#include "basefun.h"

/**
 * @brief BaseFun::GetFileArray
 * @param path
 * @param filearr
 * @param extname
 * @param subdir
 * @return
 */
unsigned int BaseFun::GetFileArray(const char *path, vector<string> &filearr,
								   const char *extname, bool subdir/* = false*/)
{
	unsigned int uFileCount = 0;
	struct dirent *pdirent = NULL;
	char buffFullPath[1024];
	DIR *dir = opendir(path);
	if (dir != NULL)
	{
		while ((pdirent = readdir(dir)) != NULL)
		{
			//string strFullPath = string(path) + string("/") + string(pdirent->d_name);
			sprintf(buffFullPath,"%s/%s", path, pdirent->d_name);
			struct stat bufstat;
			//lstat(pdirent->d_name, &bufstat);
			lstat(buffFullPath, &bufstat);
			if (S_ISREG(bufstat.st_mode))
			{
				filearr.push_back(buffFullPath);
				uFileCount++;
			}
			if (subdir == true)
			{
				if (S_ISDIR(bufstat.st_mode))
				{
					if ((strcmp(".", pdirent->d_name) != 0) &&
							(strcmp("..", pdirent->d_name) != 0))
					{
						filearr.push_back(buffFullPath);
						uFileCount++;
						uFileCount += GetFileArray(buffFullPath, filearr, extname, subdir);
					}
				}
			}
		}
	}
	return uFileCount;
}

bool IsJpg(const char *filename, struct stat *pstat)
{
	if (filename != NULL)
	{
		const char *pDot = strrchr(filename, '.');
		if (pDot != NULL)
		{
			if (strcasecmp(pDot, ".jpg") == 0)
			{
				return true;
			}
		}
	}
	return false;
}

/**
 * @brief BaseFun::SearchFile
 * @param path
 * @param filearr
 * @param pfun
 * @param iMax
 * @param subdir
 * @return
 */
unsigned int BaseFun::SearchFile(const char *path, vector<string> &filearr, PFUN_CHECKFILE pfun, int iMax,
								 bool subdir/* = false*/)
{
	DIR *pdir = NULL;
	struct dirent *pdirent =  NULL;
	struct stat bufstat;
	if ((pdir = opendir(path)) != NULL)
	{
		while ((pdirent = readdir(pdir)) != NULL)
		{
			bzero(&bufstat, sizeof(bufstat));
			char bufffullpath[512];
			sprintf(bufffullpath, "%s/%s", path, pdirent->d_name);
			stat(bufffullpath, &bufstat);
			if (S_ISDIR(bufstat.st_mode))
			{
				if ((strcmp(pdirent->d_name, ".") == 0) ||
						(strcmp(pdirent->d_name, "..") == 0))
				{

				}
				else
				{
					if (SearchFile(bufffullpath, filearr, pfun, iMax, subdir) >= iMax)
					{
						closedir(pdir);
						return filearr.size();
					}
				}
			}
			else if (S_ISREG(bufstat.st_mode))
			{
				if ((pfun == NULL) || (pfun(bufffullpath, &bufstat)))
				{
					filearr.push_back(bufffullpath);
					if (filearr.size() >= iMax)
					{
						closedir(pdir);
						return filearr.size();
					}
				}
			}
		}
		closedir(pdir);
	}
}

char *BaseFun::SplitLineForBlock(char *&pcontent, const char sep)
{
	if (pcontent == NULL)
		return NULL;
//	if (pcontent[0] == '\0')
//		return NULL;
	char *pret = pcontent;
	pcontent = strchr(pcontent, sep);
	if (pcontent != NULL)
		*pcontent++ = '\0';
	return pret;
}

char *BaseFun::SplitLineForBlock(char *&pcontent, const char *psep)
{

}

int BaseFun::SplitLine(char *pline, const char sep, const char **cols, int maxsize)
{
	char *p = pline;
	int i = 0;
	while (p != NULL)
	{
		if (i+1 > maxsize)
			break;
		cols[i++] = p;
		p = strchr(p, sep);
		if (p != NULL)
			*p++ = '\0';
	}
	return i;
}

int BaseFun::SplitLine(char *pline, const char *psep, const char **cols, int maxsize)
{
	char *p = pline;
	int icols = 0;
	int iLenSep = strlen(psep);
	while (p != NULL)
	{
		cols[icols++] = p;
		p = strstr(p, psep);
	}
}

unsigned int BaseFun::GetFileLength(const char *pfilename)
{
	struct stat buffstat;
	if (access(pfilename, 0) == 0)
	{
		lstat(pfilename, &buffstat);
		return buffstat.st_size;
	}
	return 0;
}

bool BaseFun::GetFileContent(const char *pfile, char *pbuff, unsigned int &len)
{
//	int ifile = open(p)
}

int BaseFun::ExecCmdAndGetRe(const char *pcmd, string &reD, bool bLog)
{
	string strCmdCopy = pcmd;
	strCmdCopy += " 2>&1 ";
	reD.clear();
	FILE *pfile = NULL;
	char buff[2048];

	if (NULL != (pfile = popen(strCmdCopy.c_str(), "r")))
	{
		int iRet = 0;
		if ((iRet = fread(buff, 1, 2048, pfile)) > 0)
		{
			reD = buff;
			return iRet;
		}
	}
	return -1;
}

string BaseFun::GetCurrentTime()
{
	time_t now = time(0);
	struct tm tmnow;
	localtime_r(&now, &tmnow);
	char buffTime[32];
	strftime(buffTime, 32, "%Y-%m-%d %H:%M:%S", &tmnow);
	return buffTime;
}

void BaseFun::testThread()
{
	int iRet = vfork();
	int istatus = 0;
	if (iRet == -1)
	{
		cout<<"error while create son process exit"<<endl;
		exit(0);
	}
	else if (iRet == 0)
	{
		cout<<"this is son process id:"<<getpid()<<" father processid:"<<getppid()<<endl;
		cout<<"create 4 grand son process"<<endl;
		for (int i = 0; i < 4; ++i)
		{
			int iRet2 = fork();
			if (iRet2 == 0)
			{
				cout<<"grand son process id:"<<getpid()<<" created"<<endl;
				for (;;)
				{
					cout<<"grand son sleep id:"<<getpid()<<endl;
					sleep(5);
				}
				//exit(0);
			}
		}
	}
	else if (iRet > 0)
	{
		if (waitpid(iRet, &istatus, 0) == iRet)
		{
			cout<<"waitpid success processid:"<<iRet<<" son process exited"<<endl;
		}
		cout<<"this is father thread process id:"<<getpid()<<" son porcessid:"<<iRet<<endl;
	}
	for (;;)
	{
		if (iRet == 0)
		{
			if (access("/stopson.flg", 0) == 0)
			{
				cout<<"check stop son flg"<<endl;
				exit(0);
			}
		}
		sleep(5);
	}
}

void BaseFun::test()
{
//	vector<string> vecFiles;
//	unsigned int iFileCount = GetFileArray("/home/sq", vecFiles, "", false);
//	for (int i = 0; i < iFileCount; ++i)
//	{
//		std::cout<<"path:"<<vecFiles[i]<<std::endl;
//	}
//	unsigned int iFileCount = SearchFile("/home/sq", vecFiles, IsJpg, 10, true);
//	for (int i = 0; i < iFileCount; ++i)
//	{
//		std::cout<<"path:"<<vecFiles[i]<<std::endl;
//	}

}
