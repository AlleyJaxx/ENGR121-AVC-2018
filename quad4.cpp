#include <stdio.h>
#include "E101.h"
#include "time.h"

//sensor
int front_sensor;
int left_sensor;
int right_sensor;
int front_sensor_average;
int left_sensor_average;
int right_sensor_average;

//sensor value
int near_wall =300;
int side_near_wall=400;
int sensor_threshold=1024;



int sensorRead(){

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

void goStraight(int speed){
    set_motor(1,(int)speed);   
    set_motor(2,(int)speed);
    sleep1(0,500);
} 

void stop(){
    set_motor(1,0);
    set_motor(2,0);
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

//Turn left a little
void turnLeftLittle(){ 
  set_motor(1,30);
  set_motor(2,-30);
  sleep1(0,200000);
	stop(); 

} 


//Turn right little
void turnRightLittle(){ 
  set_motor(1,-30);
  set_motor(2,30);
  sleep1(0,200000);
	stop();

} 




int main(){
	
 init();
 

if( front_sensor >= near_wall){

if(right_sensor>left_sensor){
	 turnRightLittle();
	 
	 }
	 else if (right_sensor<left_sensor){
		 turnLeftLittle();
		 
		 }
		 else{
			 goStraight(45);
			 }


}
else if(  front_sensor<= near_wall && left_sensor<=side_near_wall && right_sensor >=side_near_wall){

turnRight();
}
else if (front_sensor<= near_wall &&  left_sensor>=side_near_wall && right_sensor <=side_near_wall){
 turnLeft();
}
else if (front_sensor<= 50&&  left_sensor<=side_near_wall && right_sensor <=side_near_wall)
{
stop();
}

return 0;






}
