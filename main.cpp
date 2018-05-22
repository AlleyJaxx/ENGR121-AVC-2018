#include <stdio.h>
#include "E101.h"
#include "img_process.h"
#include <sys/time.h>

double v_go=120;
double left_bias = 1;
double Kp=120;
int quadrant = 1;

void turn(double);
void reverse();
void stop();
void openGate();
void quadrant2();
void quadrant3();

int main()
{
    //test - just makes it go forward for 2 secs
	init();
    
    //quadrant 1
    openGate();
    set_threshold();
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
	v_go = 50;
	Kp = 80;
	
    while(quadrant == 3)
    {  
        quadrant3();
        sleep1(0,100);
    }
	printf("quadrant4\n");
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
        reverse();
    }
    //Otherwise - turn based on the amount given
    else
    {
        turn(amount);
    }
}

/**
 * Line following quadrant
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
	reverse();
    }
	//Turn left - continue forward for 0.5s, turn left until white pixel in centre
	else if(amount==LEFT)
	{
		sleep1(0,500000);
		while(!wait_for_white_centre()) {
			turn(-0.7);
			sleep1(0,100);
		}
	}
	//Turn right - continue forward for 0.5s, turn right until white pixel in centre
	else if(amount==RIGHT) {
		sleep1(0,500000);
		while(!wait_for_white_centre()) {
        		turn(0.7);
		}
	
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
