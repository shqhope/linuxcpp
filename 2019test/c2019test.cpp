#include "c2019test.h"
#include <stdio.h>
#include "../basestruct/queen.h"

C2019Test::C2019Test()
{
}


int main()
{
	printf("Hello World\n");
	Queen *queen = new Queen();
	queen->Init(4);
	queen->GetFrame(0);
	return 0;
}
