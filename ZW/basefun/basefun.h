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
	static unsigned int GetFileArray(const char *path, vector<string> &filearr,
							  const char *extname, bool subdir = false);
	static unsigned int SearchFile(const char *path, vector<string> &filearr, PFUN_CHECKFILE, int iMax,
									 bool subdir = false);
public:
	static void test();
};

#endif // BASEFUN_H
