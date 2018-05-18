#include <stdio.h>
#include "E101.h"
#include "quadrant3.h"
#include <sys/time.h>

double v_go=50;
double left_bias = 1.15;
double Kp=80;

void turn(double);
void reverse();
void stop();
void quadrant3();

int main()
{
    //test - just makes it go forward for 2 secs
	init();
    
    //quadrant 1
    set_threshold();
    sleep1(1,0);
    
    while(1)
    {
        quadrant3();
		sleep1(0,100);
    }
    
    stop(); 
}

/**
 * Line following quadrant
 */
void quadrant3() {
    double amount = doScan();
    
    //If it sees no white - it is off course and will reverse
    if(amount==NO_WHITE)
    {
        reverse();
    }
	else if(amount==LEFT) {
		stop();
		sleep1(0,300000);
		turn(-0.65);
		sleep1(0,500000);
	}else if(amount==RIGHT) {
		stop();
		sleep1(0,300000);
                turn(0.65);
                sleep1(0,500000);
        }

    //Otherwise - turn based on the amount given
    else
    {
        turn(amount);
    }
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
 * Makes the robot go in reverse
 * */
void reverse() {
    int left = -(v_go*left_bias);
    int right = -(v_go);

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
