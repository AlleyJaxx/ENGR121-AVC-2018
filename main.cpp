#include <stdio.h>
#include "E101.h"

int main()
{
	init();
	set_motor(0,127);
	
	sleep1(1,0);
	set_motor(0,0);
	return 0;
}
