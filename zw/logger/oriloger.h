#ifndef ORILOGER_H
#define ORILOGER_H
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "../basefun/basefun.h"

class OriLoger
{
	static string GetLogFileName();
	static long GetLogSize();
public:
	OriLoger();

	static void WriteLog(const char *fmt, ...);
};

#endif // ORILOGER_H
