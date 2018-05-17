#include <stdio.h>
#include "E101.h"
#include "quadrant3.h"

int detectedIntersection = 0;
int timer = 0;
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
	
	//calculate number of pixels on left side of screen and right
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

	//whether all pixels on left or on right are white.
	bool all_white_left = white_pixels_left > 157.0;
	bool all_white_right = white_pixels_right > 157.0;
	
	//detects T intersection
	if (all_white_left && all_white_right) {
		timer = 0;
		if(detectedIntersection!=1){
			detectedIntersection = 1;
			if(DEBUG) {
				printf("T\n");
			}
		}
		return 0;
	//Intersection on left only
	} else if (all_white_left) {
		timer = 0;
		if(detectedIntersection==0){
			detectedIntersection = 2;
		
			if(DEBUG) {
				printf("Left\n");
			}
		}else if(detectedIntersection==3){
			detectedIntersection=2;
			if(DEBUG){
				printf("T\n");
			}
		}
		return 0;
	//Intersection on right only
	} else if (all_white_right) {
		timer = 0;
		if(detectedIntersection==0){
			detectedIntersection = 3;
		
			if(DEBUG) {
				printf("Right\n");
			}
		}else if(detectedIntersection==2){
			detectedIntersection=1;
			if(DEBUG){
                                printf("T\n");
                        }

		}
		return 0;
	}
	
	//Detects only black
	if (white_pixels_left + white_pixels_right < 3) {
		//printf("All black\n");
		//TURN RIGHT
		if(detectedIntersection==3){
			if(DEBUG){
				printf("Turning Right\n");
			}
			return 0.4;
		//TURN LEFT
		}else if(detectedIntersection==2 || detectedIntersection==1){
			if(DEBUG){
				printf("Turning Left\n");
			}
			return -0.4;
		//DEAD END
		}else{
			return NO_WHITE;
		}
	}
	
	//wants to go straight but intersection seen previously, keep going straight for n more checks
	if(detectedIntersection!=0){
		timer++;
		//n checks before it continues following the line.
		if(timer<15) {
			return 0;
		}
	}
	detectedIntersection = 0;
	//Go forward
	//printf("Forward\n");
	double average_white_location = white_location / (white_pixels_right + white_pixels_left);
	
	return average_white_location;
}
