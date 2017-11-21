#ifndef ORILOGER_H
#define ORILOGER_H
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

class OriLoger
{
public:
	OriLoger();

	static void WriteLog(const char *fmt, ...);
};

#endif // ORILOGER_H
