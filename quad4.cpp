#include <stdio.h>
#include "E101.h"
#include "time.h"
#include "img_process.h"
#include "quad4.h"
#include <list>

//checking variables
bool gate_down = false;
bool seen_gate = false;
bool wait_gate = false;
int frames = 0;
std::list<double> left_check;
std::list<double> right_check;
std::list<double> forward_check;

//sensors
double front_sensor;
double left_sensor;
double right_sensor;

//sensor value
const double near_wall =210;
const double side_near_wall=400;
const double hug_right_threshold=550;
bool DEBUG2 = false;
   
/**
* Used for getting the robot unstuck
*/
int waitForWallDetect() {
	sensor_read();

	if(right_sensor>450) {
		return 1;
	}else if(left_sensor>450) {
		return -1;
	}else{
		return 0;
	}
}

/**
* Find a red pixel in the image
*/
bool check_red2()
{
	take_picture();
	
	for(int x = 120; x<200; x++) {
		int r = get_pixel(120,x,0);
		int g = get_pixel(120,x,1);
		int b = get_pixel(120,x,2);
		if(DEBUG2) {
			printf("%d,%d,%d\n",r,g,b);
		}
		if(r-b>50 && r>120) {
			return true;
		}
	}
	return false;
}


/**
* Reads the values in all the sensors
*/
void sensor_read() {
	front_sensor = (double)read_analog(0);
	left_sensor = (double)read_analog(1);
	right_sensor = (double)read_analog(2);
}

/**
* Checks if the robot is stuck to see if the sensors aren't changing much
*/
bool checkIfStuck() {
	left_check.push_back(left_sensor);
	right_check.push_back(right_sensor);
	forward_check.push_back(front_sensor);
	printf("%d\n",left_check.size());
	if(left_check.size()>30) {
		left_check.pop_front();
		right_check.pop_front();
		forward_check.pop_front();
		
		std::list<double>::iterator it;
		
		//left sensor check
		//double left = 0;
		double left_min = 1024;
		double left_max = 0;
		for(it = left_check.begin(); it != left_check.end(); ++it) {
			double value = *it;
			//left+=value;
			if(value<left_min) left_min = value;
			if(value>left_max) left_max = value;
		}
		double left_range = left_max-left_min;
		
		//right sensor check
		//double right = 0;
		double right_min = 1024;
		double right_max = 0;
		for(it = right_check.begin(); it != right_check.end(); ++it) {
			double value = *it;
			//right+=value;
			if(value<right_min) right_min = value;
			if(value>right_max) right_max = value;
		}
		double right_range = right_max-right_min;
		
		//forward sensor check
		//double forward = 0;
		double forward_min = 1024;
		double forward_max = 0;
		for(it = forward_check.begin(); it != forward_check.end(); ++it) {
			double value = *it;
			//forward+=value;
			if(value<forward_min) forward_min = value;
			if(value>forward_max) forward_max = value;
		}
		double forward_range = forward_max-forward_min;
		printf("%f,%f,%f\n",left_range,right_range,forward_range);
		return(left_range < 90 && right_range < 90 && forward_range < 90 && front_sensor>100 && left_sensor<400 && right_sensor<400);
	}
	return false;
}

/**
* Main function for quadrant 4 turning
*/
double quadrant4_turn(){
    sensor_read();
    if(DEBUG2) {
        printf("%f | %f | %f\n",front_sensor,left_sensor,right_sensor);
    }
	frames++;
    //wait at gate
    if((check_red2() || wait_gate) &&  !seen_gate && frames>100){
		if(!wait_gate) {
			wait_gate = true;
			if(DEBUG2) {
				printf("RED DETECTED\n");
			}
			return GATE;
		}
		//sees gate
        if(front_sensor>100){
            gate_down=true;
            return WAIT;
        }
		//does not see gate
        else{
			//continue
            if(gate_down){
				seen_gate = true; 
            	frames = 0;
			//wait for gate to come down
            }else{
				return WAIT;
            }
        }
    }
	
	//stuck check
	if(checkIfStuck()) {
		return STUCK;
	}
	
	
    //ok to go forward
    if( front_sensor <= near_wall){
		//right wall detected
		if(right_sensor>side_near_wall) {
            double error = hug_right_threshold-right_sensor;
            if(DEBUG2) {
				printf("STRAIGHT: %f,%f\n",right_sensor,error);
			}
			error/=500.0;
			
			if(error>1){error=1;}
			if(error<-1){error=-1;}
			return error;
        //only sees left wall
        }else if(left_sensor>side_near_wall) {
            double error = left_sensor-hug_right_threshold;
            if(DEBUG2) {
				printf("STRAIGHT: %f,%f\n",left_sensor,error);
			}
			error/=500.0;
			
			if(error>1){error=1;}
			if(error<-1){error=-1;}
			return error;
		//does not see either wall
        }else{
			return 0;
            //return STUCK;
        }
	}
	//detects wall in front
	else {
	double value = (double)front_sensor/450.0;
        if(right_sensor>left_sensor) {
			return -value;
		}
		else {
			return value;
		}
    }
}
