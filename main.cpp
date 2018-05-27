#include <stdio.h>
#include "E101.h"
#include "img_process.h"
#include "quad4.h"
#include <sys/time.h>

double v_go=50;
double Kp=70;
int quadrant = 1;

void turn(double);
void reverse(double);
void stop();
void openGate();
void quadrant2();
void quadrant3();
void quadrant4();

int main()
{
    //test - just makes it go forward for 2 secs
	init();
	/*while(1){
		printf("%d\n",count_white_test());
		set_threshold();
	}*/
    //quadrant 1
    openGate();
    
    sleep1(0,500000);
    
    //quadrant 2
    printf("quadrant2\n");
    quadrant = 2;
    
    while(quadrant == 2)
    {
        quadrant2();
	sleep1(0,100);
    }
	printf("quadrant3\n");
	
    while(quadrant == 3)
    {  
        quadrant3();
        sleep1(0,100);
    }
	v_go = 30;
	Kp = 50;
	printf("quadrant4\n");
	while(quadrant == 4)
	{
		quadrant4();
		sleep1(0,100);
	}
	printf("end\n");
    stop();
}


/**Open gate 1*/
void openGate() {
    char server_addr[15] = "130.195.6.196";
	int port = 1024;
	char message[24] = "Please";

	connect_to_server(server_addr, port);
	send_to_server(message);
	receive_from_server(message);
	send_to_server(message);
}


/**
 * Line following quadrant
 */
void quadrant2() {
    double amount = quadrant2_turn();
    //If it sees all white - it is on the next section (break for now)
    if(amount==ALL_WHITE)
    {
        quadrant = 3;
    }
    //If it sees no white - it is off course and will reverse
    else if(amount==NO_WHITE)
    {
        reverse(0);
    }
    //Otherwise - turn based on the amount given
    else
    {
        turn(amount);
    }
}

/**
 * Line maze quadrant
 */
void quadrant3() {
    double amount = quadrant3_turn();
	
    //If it sees no white - it is off course and will reverse
    if(amount==NO_WHITE)
    {
        /*stop();
	sleep1(0,300000);
	set_motor(2,(int)(60.0*left_bias));
	set_motor(1,-60);
	sleep1(1,0);*/
	sleep1(0,150000);
	stop();
	sleep1(0,300000);
	while(!wait_for_white_centre(60)) {
		turn(0.5);
	}
	stop();
	sleep1(0,300000);
    }
	//Turn left - continue forward for 0.5s, turn left until white pixel in centre
	else if(amount==LEFT)
	{
		sleep1(0,150000);
		stop();
		sleep1(0,300000);
		while(!wait_for_white_centre(-60)) {
			turn(-0.5);
		}
		stop();
		sleep1(0,300000);
	}
	//Turn right - continue forward for 0.5s, turn right until white pixel in centre
	else if(amount==RIGHT) {
		sleep1(0,150000);
		stop();
		sleep1(0,300000);
		while(!wait_for_white_centre(60)) {
        		turn(0.5);
		}
		stop();
		sleep1(0,300000);
	}
	//finish quadrant 3
	else if(amount==RED)
	{
		quadrant = 4;
	}
    //Otherwise - turn based on the amount given
	else
    {
        turn(amount);
    }
}

/**
* Walled maze quadrant
*/
void quadrant4() {
	double amount = quadrant4_turn();
	//detects end?
	if(amount==STOP) {
		quadrant = 5;
	//left
	}else if(amount==LEFT) {
		turn(-1.2);
	//right
	}else if(amount==RIGHT) {
		turn(1.2);
	//wait at the gate
    }else if(amount==GATE) {
        stop();
	}else if(amount==STUCK) {
        reverse(0);
	//straight
	}else {
		turn(amount);
	}
	
}

/**
 * Turns the robot
 * */
void turn(double amount){
    int left= (int)(v_go+Kp*amount);
    int right= (int)(v_go-Kp*amount);
    set_motor(2,left);
    set_motor(1,right);
}

/**
 * Makes the robot go in reverse
 * */
void reverse(double amount) {
    int left = -(int)(v_go+Kp*amount);
    int right = -(int)(v_go-Kp*amount);

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
