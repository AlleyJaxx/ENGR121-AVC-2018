#include <stdio.h>
#include "E101.h"
#include "image_processing.h"

int main()
{
    //test - just makes it go forward for 2 secs
	init();
	
	//set the threshold when turning it on
	set_threshold();
	
	for(int i = 0;i<10;i++)
	{
		sleep1(1,0);
		printf("Test %d: %f\n",i,get_turn());
	}
	
	return 0;
}
