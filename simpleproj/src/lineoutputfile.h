#ifndef LINEOUTPUTFILE_H
#define LINEOUTPUTFILE_H
#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

class LineOutputFile
{
	FILE*	m_pFile;
	string	m_strFileName;
	int		m_tmLastMod;
	int		m_iLineCount;
public:
	LineOutputFile();
	void InsertOneLine(const char *pline);
	void Flush();
};

#endif // LINEOUTPUTFILE_H
