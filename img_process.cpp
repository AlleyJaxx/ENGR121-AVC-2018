#include "E101.h"
#include "img_process.h"
#include <stdio.h>

int white_threshold = 127;
int detectedIntersection = 0;
int timer = 0;
bool DEBUG = false;

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
	int threshold = (max_white+min_white)/2;
	
	if(max_white-min_white<50 || threshold>180 || threshold<80){
		return;
	}
	printf("%s\n",threshold);
	white_threshold = threshold;
	if(DEBUG)
	{
		printf("Thres: %d. Min=%d, Max=%d\n",white_threshold,min_white,max_white);
	}
}

/**
 * This will return a value between -1 and 1 of where the white line is. 0 is the exact centre. 1 is all the way to right, -1 is all the way to left
 * */
double get_turn()
{
	
	//get picture
    take_picture();
	if(DEBUG){
		printf("-----\n");
}
	
    int white_pixels = 0;
    double white_location = 0;
    
	int y = 120;
    for(int x=0;x<320;x++)
    {
		double percent_location = ((double)x-160.0)/160.0;
		int white = get_pixel(y,x,3);
		//detect white
		if(white>white_threshold)
		{
			white_location += percent_location;
			white_pixels++;
		}
	}

	//no white pixels
	if(white_pixels<3)
	{
		if(DEBUG)
		{
			printf("no white\n");
		}
		return NO_WHITE;
	}
	if(white_pixels>317)
    {
        if(DEBUG)
        {
            printf("all white\n");
        }
        return ALL_WHITE;
    }
	
	//reset threshold
	if(white_pixels>50 && white_pixels < 270) {
		set_threshold();
	}
	//average location of the white pixels
	double average_white_location = white_location/white_pixels;
	
	if(DEBUG)
	{
		printf("%d white. avg loc = %f\n",white_pixels,average_white_location);
	}
	
	return average_white_location;
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
	bool all_white_left = white_pixels_left > 130.0;
	bool all_white_right = white_pixels_right > 130.0;
	
	//detects T intersection
	if (all_white_left && all_white_right) {
		timer = 0;
		if(detectedIntersection!=1){
			detectedIntersection = 1;
			if(DEBUG) {
				printf("T intersect\n");
			}
		}
		return 0;
	//Intersection on left only
	} else if (all_white_left) {
		timer = 0;
		if(detectedIntersection==0){
			detectedIntersection = 2;
			if(DEBUG) {
				printf("Left intersect\n");
			}
		}else if(detectedIntersection==3){
			detectedIntersection=2;
			if(DEBUG){
				printf("T intersect\n");
			}
		}
		return 0;
	//Intersection on right only
	} else if (all_white_right) {
		timer = 0;
		if(detectedIntersection==0){
			detectedIntersection = 3;
			if(DEBUG) {
				printf("Right intersect\n");
			}
		}else if(detectedIntersection==2){
			detectedIntersection=1;
			if(DEBUG){
                printf("T intersect\n");
            }
		}
		return 0;
	}
	
	//Detects only black - at the end of an intersection - turn the correct direction
	if (white_pixels_left + white_pixels_right < 40) {
		
		//detectedIntersection = 0;
		
		//TURN RIGHT
		if(detectedIntersection==3){
			if(DEBUG){
				printf("Turning Right\n");
			}
			detectedIntersection = 0;
			return RIGHT;
		//TURN LEFT
		}else if(detectedIntersection==2 || detectedIntersection==1){
			if(DEBUG){
				printf("Turning Left\n");
			}
			detectedIntersection = 0;
			return LEFT;
		//DEAD END
		}else{
			if(DEBUG){
				printf("Dead end?\n");
			}
			detectedIntersection = 0;
			return NO_WHITE;
		}
		
		//printf("All black\n");
		//return turn_value;
	}
	
	//wants to go straight but intersection seen previously, keep going straight for n more checks
	if(detectedIntersection!=0){
		timer++;
		//n checks before it continues following the line.
		if(timer<20) {
			return 0;
		}
		if(DEBUG){
			printf("Continuing forward\n");
		}
	}
	//reset variables
	detectedIntersection = 0;
	//turn_value = NO_WHITE;
	
	//printf("following\n");
	//Go forward
	//printf("Forward\n");
	double average_white_location = white_location / (white_pixels_right + white_pixels_left);
	
	return average_white_location;
}

