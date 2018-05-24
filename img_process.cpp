#include "E101.h"
#include "img_process.h"
#include <stdio.h>

int white_threshold = 127;
int detectedIntersection = 0;
int timer = 0;
bool DEBUG = true;

int count_white_test()
{
	set_threshold();
	take_picture();
	int y = 120;
	int white_pixels = 0;
	for(int x = 0; x<320; x++){
		int white = get_pixel(120,x,3);
		if(white>white_threshold){white_pixels++;}
	}
	return white_pixels;
}

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
	//range
	int range = max_white-min_white;
	
	//detects only black
	if(max_white<120 && range<80)
	{
		white_threshold = 255;
	//detects only white
	}else if(min_white>100 && range<150) {
		white_threshold = 0;
	//mixed detection
	}else{
		white_threshold = (max_white+min_white)/2;
	}
	if(DEBUG)
	{
		printf("Thres: %d. Min=%d, Max=%d\n",white_threshold,min_white,max_white);
	}
}

/**
* returns whether or not white is in the centre
*/
bool wait_for_white_centre()
{
	set_threshold();

	take_picture();

	int white = get_pixel(120,160,3);
	return white > white_threshold;
}

	
/*
* returns whether it can see red
*/
bool check_red()
{
	take_picture();
	
	int r = get_pixel(120,160,0);
	int g = get_pixel(120,160,1);
	int b = get_pixel(120,160,2);
	return (r>180 && g<100 && b<100);
}

/**
 * Quadrant 2
 * */
double quadrant2_turn()
{
	set_threshold();
	
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
	printf("%d\n",white_pixels);
	//all white pixels
	if(white_pixels>300)
    	{
        	if(DEBUG)
        	{
            		printf("all white\n");
        	}
        	return ALL_WHITE;
    	}
	
	//average location of the white pixels
	double average_white_location = white_location/white_pixels;
	
	if(DEBUG)
	{
		printf("%d white. avg loc = %f\n",white_pixels,average_white_location);
	}
	
	return average_white_location;
}

/**
* Quadrant 3
*/
double quadrant3_turn() {
	set_threshold();
	if(check_red()){
		return RED;
	}
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
	bool all_white_left = white_pixels_left > 155.0;
	bool all_white_right = white_pixels_right > 155.0;
	
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
			detectedIntersection=1;
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
	
	//go straight if a lot of white pixels
	/*if(white_pixels_right + white_pixels_left > 200) {
		return 0;
	}*/
	//reset variables
	detectedIntersection = 0;
	
	//Go forward
	double average_white_location = white_location / (white_pixels_right + white_pixels_left);
	
	return average_white_location;
}

