#include <stdio.h>
#include "E101.h"
#include "time.h"
#include "quad4.h"

//sensor
int front_sensor;
int left_sensor;
int right_sensor;
int front_sensor_average;
int left_sensor_average;
int right_sensor_average;

//sensor value
const int near_wall =250;
const int side_near_wall=400;
const int hug_right_threshold=610;

int sensorRead(){
	front_sensor = 0;
	left_sensor = 0;
	right_sensor = 0;
    for(int i=0;i<5;i++){
	front_sensor = front_sensor + read_analog(0);
    left_sensor = left_sensor + read_analog(1);
    right_sensor = right_sensor + read_analog(2);
     printf("front_sensor:%d,left_sensor:%d,right_sensor:%d\n",front_sensor,left_sensor,right_sensor);
    }
 front_sensor_average=front_sensor/5;
 left_sensor_average=left_sensor/5;
 right_sensor_average=right_sensor/5;
 printf("front_sensor_average:%d,left_sensor_average:%d,right_sensor_average:%d\n",front_sensor_average,left_sensor_average,right_sensor_average);

}


void turnLeft(){
	set_motor(1,60);
  set_motor(2,-60);
  sleep1(2,0);
	stop(); 
	}

void turnRight(){
	set_motor(1,-60);
  set_motor(2,60);
  sleep1(2,0);
	stop();
	
	}

double quad4(){
	 

	if( front_sensor_average >= near_wall){
		
		//hug right
		if(right_sensor_average>side_near_wall) {
			double error = hug_right_threshold-right_sensor_average;//difference between right and threshold. negative means needs to turn left
			return error/600.0;//600 is some random value to make the error similar to between -1 and 1. Might not be accurate though.
		}
		//if no right hug left
		else if(left_sensor_average>side_near_wall) {
			double error = left_sensor_average-hug_right_threshold;//difference between threshold and left. negative means needs to turn left
			return error/600.0;//600 is some random value to make the error similar to between -1 and 1. Might not be accurate though.
		//if no walls go straight
		}else{
			return 0;
		}


	}
	else if(  front_sensor_average<= near_wall && left_sensor_average<=side_near_wall && right_sensor_average >=side_near_wall){

		return RIGHT;
	}
	else if (front_sensor_average<= near_wall &&  left_sensor_average>=side_near_wall && right_sensor_average <=side_near_wall){
	 return LEFT;
	}
	else if (front_sensor_average<= 50&&  left_sensor_average<=side_near_wall && right_sensor_average <=side_near_wall)
	{
	return STOP;
	}
}
