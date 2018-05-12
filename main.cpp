#include <stdio.h>
#include "E101.h"
#include "img_process.h"
#include <sys/time.h>

double v_go=50;
double left_bias = 1.15;
double Kp=100;

void turn(double);
void stop();

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
		long elapsed = (t2.tv_sec -t1.tv_sec);
		if(elapsed>10)
		{
			break;
		}
		sleep1(0,50);
    }
    
    stop(); 
}

/**
 * Turns the robot
 * */
void turn(double amount){
    int left= (int)((v_go+Kp*amount)*left_bias);
    int right= (int)(v_go-Kp*amount);
    set_motor(2,left);
    set_motor(1,right);
}

/**
 * Stops the robot
 * */
void stop(){
    set_motor(1,0);
    set_motor(2,0);
}
