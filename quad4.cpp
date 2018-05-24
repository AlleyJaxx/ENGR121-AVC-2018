#include <stdio.h>
#include "E101.h"
#include "time.h"
#include "quad4.h"

//sensor
double front_sensor;
double left_sensor;
double right_sensor;
bool gateDown=false;
bool gate_down=false;
bool seen_gate=false;
//sensor value
const double near_wall =250;
const double side_near_wall=400;
const double hug_right_threshold=610;

int sensorRead() {
	front_sensor = (double)read_analog(0);
	left_sensor = (double)read_analog(1);
	right_sensor = (double)read_analog(2);
}

    
bool check_red()
{
	take_picture();
	
	int r = get_pixel(120,160,0);
	int g = get_pixel(120,160,1);
	int b = get_pixel(120,160,2);
	return (r>225 && g<150 && b<150);
}

void turnLeft(){
	set_motor(1,0);
	set_motor(2,0);
	sleep1(1,0);
	set_motor(1,60);
  set_motor(2,-60);
  sleep1(2,0);
	 
	}

void turnRight(){
	set_motor(1,0);
	set_motor(2,0);
	sleep1(1,0);
	set_motor(1,-60);
  	set_motor(2,60);
  	sleep1(2,0);
	
	
	}
	

double quad4(){
   
    if(check_red() && !seen_gate){ 
        if(front_sensor>300){
            gate_down=true;
            return GATE;
            
        }
        else{
            if(gate_down=true){
                seen_gate = true; 
            
            }else{
                return GATE;
            }
        }
    }
	 printf("%f,%f,%f\n",front_sensor,right_sensor,left_sensor);
	sensorRead();
	if( front_sensor <= near_wall){
		
		//hug right
		//if(right_sensor>250 && left_sensor>250) {
			double error = left_sensor-right_sensor;//difference between right and left. negative means needs to turn left
			printf("STRAIGHT: %f,%f\n",right_sensor,error);
			error/=100.0;
			
			if(error>1){error=1;}
			if(error<-1){error=-1;}
			return error;//600 is some random value to make the error similar to between -1 and 1. Might not be accurate though.
		//if no walls go straight
		//}else{
		//	return 0;
		//}


	}
	else {
		return STOP;
	}
}
