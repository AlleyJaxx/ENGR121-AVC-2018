#include "E101.h"
#include "img_process.h"
#include <stdio.h>

bool DEBUG = true;

int white_threshold = 127;

/**
* Sets the threshold value for checking white
*/
void set_threshold()
{
	//get picture
    take_picture();
	
	if(DEBUG)
	{
		char filename[5] = "test";
		save_picture(filename);
	}
    
    //determine minimum and maximum shades of white in the picture
    int min_white = 255;
    int max_white = 0;
    
    int y = 120;
    for(int x=0;x<320;x++)
    {
		int white = get_pixel(y,x,3);
        printf(white + " ");
		if(white>max_white)
		{
			max_white = white;
		}
		if(white<min_white)
		{
			min_white = white;
		}
	}
	//threshold
	white_threshold = min_white+(max_white-min_white)/2;
	
	if(DEBUG)
	{
		printf("\nThres: %d. Min=%d, Max=%d\n",white_threshold,min_white,max_white);
	}
}

/**
 * This will return a value between -1 and 1 of where the white line is. 0 is the exact centre. 1 is all the way to right, -1 is all the way to left
 * */
double get_turn()
{
	if(DEBUG)
	{
		printf("---------\n");
	}
	//get picture
    take_picture();
	
    int white_pixels = 0;
    double white_location = 0;
    
	int y = 120;
    for(int x=0;x<320;x++)
    {
		double percent_location = (x-160.0)/160.0;//-1 = completely to left, 1 = completely to right, 0 = centre
		int white = get_pixel(y,x,3);
		//detect white
		if(white>white_threshold)
		{
			white_pixels++;
			if(DEBUG)
			{
				printf("white (%d) at x=%d. Loc=%d\n",white,x,percent_location);
			}
			white_location += percent_location;
		}
	}

	//no white pixels
	if(white_pixels==0)
	{
		if(DEBUG)
		{
			printf("no white\n");
		}
		return 0;
	}
	

	//average location of the white pixels
	double average_white_location = white_location/white_pixels;
	
	if(DEBUG)
	{
		printf("%d white. avg loc=%d\n",white_pixels,average_white_location);
	}
	
	return average_white_location;
}
