#include <stdio.h>
#include "E101.h"
#include "img_process.h"
#include <sys/time.h>

double v_go=50;
double left_bias = 1.15;
double Kp=100;
int quadrant = 1;

void turn(double);
void reverse();
void stop();
void openGate();
void quadrant2();

int main()
{
    //test - just makes it go forward for 2 secs
	init();
    
    //quadrant 1
    openGate();
    set_threshold();
    sleep1(1,0);
    
    //quadrant 2
    quadrant = 2;
    
    while(quadrant == 2)
    {
        quadrant2();
		sleep1(0,1000);
    }
    
    stop(); 
}

/**
 * Line following quadrant
 */
void quadrant2() {
    double amount = get_turn();
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
