#include <stdio.h>
#include "E101.h"

double test_threshold();

int main()
{
    //test - just makes it go forward for 2 secs
	init();

	while(1) {
        test_threshold();
        sleep1(1,0);
    }
	return 0;
}

double test_threshold()
{
	//get picture
    take_picture();
    
    //determine minimum and maximum shades of white in the picture
    int min_white = 255;
    int max_white = 0;
    
    int y = 120;
    for(int x=0;x<320;x++)
    {
		int white = get_pixel(y,x,3);
		if(white>max_white)
		{
			max_white = white;
		}
		if(white<min_white)
		{
			min_white = white;
		}
	}
	int range = max_white-min_white;
	printf("Min=%d Max=%d Range=%d\n",min_white,max_white,range);
}
