#include <stdio.h>
#include "E101.h"
#include "quad4.h"
double v_go=120;
double left_bias = 1;
double Kp=120;

void turn(double);
void stop();
void reverse();
void quadrant4();

bool running = true;

int main()
{
    init();
    while(running){
		quadrant4();
	}
	stop();
}

void quadrant4() {
	double amount = quad4();
	if(amount==STOP) {
		running = false;
	}else if(amount==LEFT) {
		turnLeft();
	}else if(amount==RIGHT) {
		turnRight();
    }else if(amount==GATE) {
        stop();
	}else {
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
