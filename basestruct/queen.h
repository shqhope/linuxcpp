#ifndef QUEEN_H
#define QUEEN_H
#include "heads.h"


class Queen
{
	char **ppQueen;
	int m_size;
public:
	Queen();
	void Init(int size);
	void printQ();
	void GetFrame(int row, int &iframe);
	bool goodPoint(const int &row, const int &col);
};

#endif // QUEEN_H
