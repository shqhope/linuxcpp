#include "functions.h"

const char *swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
	return __FILE__;
}

void queen()
{

}
