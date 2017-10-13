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
