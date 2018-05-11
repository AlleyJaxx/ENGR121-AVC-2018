#include <stdio.h>
#include "E101.h"

void turn(double);
void stop();

int main()
{
    init();
    turn(0);
    sleep1(3,500000);
    turn(-1);
    sleep1(3,0);
    turn(-0.5);
    sleep1(3,0);
    turn(0);
    sleep1(3,0);
	turn(0.5);
    sleep1(3,0);
    turn(1);
    sleep1(3,0);
    stop();
   
    
}
void turn(double amount){
    int v_go=100;
    int Kp=50;
    int left=0;
    int right=0;
    left= v_go+Kp*amount;
    right= v_go-Kp*amount;
    set_motor(1,left);
    set_motor(2,right);
}
void stop(){
    set_motor(1,0);
    set_motor(2,0);
}
