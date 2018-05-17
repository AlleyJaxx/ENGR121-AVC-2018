#include <stdio.h>
#include "E101.h"
#include "quadrant3.h"

int detectedInstersection = 0;

int white_threshold = 127;

bool DEBUG = true;

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
		printf("Thres: %d. Min=%d, Max=%d\n",white_threshold,min_white,max_white);
	}
}

double doScan() {
	
	take_picture();
	
	int white_pixels_left = 0;
	int white_pixels_right = 0;
	
	double white_location = 0;
	
	int y = 120;
	
	for (int x = 0; x < 320; x++) {
		
		double percent_location = ((double)x - 160.0) / 160.0;
		int white = get_pixel(y, x, 3);
		
		if (white > white_threshold){
		
			white_location += percent_location;
			if (x < 160.0) {
				white_pixels_left++;
					
			} else {	
				white_pixels_right++;
				
			}
			
			
			
		}
	
	}

	
	bool all_white_left = white_pixels_left > 157.0;
	
	bool all_white_right = white_pixels_right > 157.0;
		
	
	if (all_white_left && all_white_right) {
		detectedInstersection = 1;
		printf("T\n");
		
		return 0;
	} else if (all_white_left && !all_white_right) {
		
		detectedInstersection = 2;
		printf("Left\n");
		return 0;
		
	} else if (!all_white_left && all_white_right) {
		
		detectedInstersection = 3;
		printf("Right\n");
		return 0;
	} else {
		
		detectedInstersection = 0;
		
	}
	
	if (white_pixels_left + white_pixels_right < 3) {
		printf("REVERSE\n");
		return NO_WHITE;
		
		
		
	}
	
	printf("FORWARD\n");
	double average_white_location = white_location / (white_pixels_right + white_pixels_left);
	
	return average_white_location;
	
		
		
	
}
