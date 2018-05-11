#include <stdio.h>
#include "E101.h"
#include <sys/time.h>

double v_go=50;
double left_bias = 1.15;
double Kp=30;

int white_threshold = 127;

void set_threshold()
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
	//threshold
	white_threshold = min_white+(max_white-min_white)/2;
}

/**
 * This will return a value between -1 and 1 of where the white line is. 0 is the exact centre. 1 is all the way to right, -1 is all the way to left
 * */
double get_turn()
{
	//get picture
    take_picture();
	
    int white_pixels = 0;
    double white_location = 0;
    
    for(int x=0;x<320;x++)
    {
		double percent_location = (x-160)/160;//-1 = completely to left, 1 = completely to right, 0 = centre
		int white = get_pixel(y,x,3);
		//detect white
		if(white>threshold)
		{
			white_pixels++;
			white_location += percent_location;
		}
	}
	//no white pixels
	if(white_pixels==0)
	{
		return 0;
	}
	//average location of the white pixels
	double average_white_location = white_location/white_pixels;
	return average_white_location;
}

int main()
{
    //test - just makes it go forward for 2 secs
	init();
    set_threshold();
    
    struct timeval t1;
    struct timeval t2;
    gettimeofday(&t1,0);
    
    while(1)
    {
        double amount = get_turn();
        turn(amount);
        
		gettimeofday(&t2,0);
		//break after 10 seconds
		long elapsed = (t2.tv_sec -t1.tv_sec)
		if(elapsed>10)
		{
			break;
		}
		sleep1(0,50);
    }
    
    stop(); 
}
void turn(double amount){
    int left=0;
    int right=0;
    left= (int)((v_go+Kp*amount)*left_bias);
    right= (int)(v_go-Kp*amount);
    printf("%d,%d\n",left,right);
    set_motor(2,left);
    set_motor(1,right);
}
void stop(){
    set_motor(1,0);
    set_motor(2,0);
}
