#include "oriloger.h"

OriLoger::OriLoger()
{

}

void OriLoger::WriteLog(const char *fmt, ...)
{
	char buffLine[1024];
	char buffOut[1024];
	va_list args;
	va_start(args, fmt);
	int isize = vsnprintf(buffLine, 1000, fmt, args);
	va_end(args);

	string strTime = BaseFun::GetCurrentTime();
	sprintf(buffOut, "%s %s", strTime.c_str(), buffLine);

	cout<<buffOut<<endl;
}
