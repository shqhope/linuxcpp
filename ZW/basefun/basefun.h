#ifndef BASEFUN_H
#define BASEFUN_H
#include <unistd.h>
#include <dirent.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

class BaseFun
{
	typedef bool (*PFUN_CHECKFILE)(const char *filename, struct stat *pstat);
public:
	/**
	 * @brief 获取文件列表
	 * @param path
	 * @param filearr
	 * @param extname
	 * @param subdir
	 * @return 
	 */
	static unsigned int GetFileArray(const char *path, vector<string> &filearr,
							  const char *extname, bool subdir = false);
							  
	/**
	 * @brief 
	 * @param path
	 * @param filearr
	 * @param iMax
	 * @param subdir
	 * @return 
	 */
	static unsigned int SearchFile(const char *path, vector<string> &filearr, PFUN_CHECKFILE, int iMax,
									 bool subdir = false);
	
	///2017 10 27
	/**
	 * @brief  分割行
	 * @param pcontent
	 * @param sep
	 * @return 
	 */
	static char *SplineForBlock(char *pcontent, char sep);
	static int SpliteLine(char *pline, char sep, int maxsize);
	static unsigned int GetFileLength(const char *pfilename);
	static bool GetFileContent(const char *pfile, char *pbuff, unsigned int &len);
public:
	static void test();
};

#endif // BASEFUN_H
