#include <stdio.h>
#include "E101.h"
#include "quad4.h"

void turn(double);
void stop();

int main()
{
    init();
    while(1){
		quad4();
	}
}
void turn(double amount){
    double v_go=50;
    double left_bias = 1.15;
    double Kp=30;
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
