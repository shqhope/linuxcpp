#ifndef QUEEN_H
#define QUEEN_H
#include "heads.h"


class Queen
{
	char **ppQueen;
	int m_size;
	bool goodPoint(const int &row, const int &col);

public:
	Queen();
	void Init(int size);
	void printQ();
	void GetFrame(int row);
};

#endif // QUEEN_H
