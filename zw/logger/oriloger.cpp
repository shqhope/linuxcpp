#include "oriloger.h"

OriLoger::OriLoger()
{

}

void OriLoger::WriteLog(const char *fmt, ...)
{
	char buffLine[1024];

	va_list args;
	va_start(args, fmt);
	int isize = vsnprintf(buffLine, 1022, fmt, args);
	va_end(args);

}
