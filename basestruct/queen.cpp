#include "queen.h"

Queen::Queen()
{

}

void Queen::Init(int size)
{
	m_size = size;
	ppQueen = new char*[size];
	for (int i = 0; i < size; ++i)
	{
		ppQueen[i] = new char[size];
		for (int row = 0; row < size; ++row)
		{
			*(*(ppQueen+i)+row) = '0';
		}
	}
}

void Queen::printQ()
{
	for (int col = 0; col < m_size; ++col)
	{
		for (int row = 0; row < m_size; ++row)
		{
			printf("%c ", *(*(ppQueen + col) + row));
		}
		printf("\n");
	}
}

bool Queen::goodPoint(const int &row, const int &col)
{
	for (int irow = 0; irow < row; ++irow)
	{
		if (*(*(ppQueen+irow)+col) == '*')
		{
			return false;
		}
		for (int icol = 0; icol < m_size; ++icol)
		{
			if (*(*(ppQueen+irow)+icol) == '*')
			{
				if (abs(row-irow) == abs(col - icol))
				{
					return false;
				}
			}
		}
	}
	return true;
}

void Queen::GetFrame(int row)
{
	if (row == m_size)
	{
		printf("one frame\n");
		printQ();
		printf("\n");
	}
	for (int col = 0; col < m_size; ++col)
	{
		if (goodPoint(row, col))
		{
			*(*(ppQueen+row)+col)='*';
			GetFrame(row+1);
			*(*(ppQueen+row)+col)='0';
		}
	}
}
