#include <stdio.h>
#include "E101.h"
#include "time.h"
#include "img_process.h"

//bools
bool gateDown=false;
bool gate_down=false;
bool seen_gate=false;

int low_left = 0;
int low_right = 0;
//sensor value
const double near_wall =210;
const double side_near_wall=500;
const double hug_right_threshold=550;
bool DEBUG2 = false;
    
bool check_red2()
{
	take_picture();
	
	int r = get_pixel(120,160,0);
	int g = get_pixel(120,160,1);
	int b = get_pixel(120,160,2);
	return (r>225 && g<150 && b<150);
}
	

double quadrant4_turn(){
    double front_sensor = (double)read_analog(0);
	double left_sensor = (double)read_analog(1);
	double right_sensor = (double)read_analog(2);
    if(DEBUG2) {
        printf("%f,%f,%f\n",front_sensor,right_sensor,left_sensor);
    }
    //wait at gate
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
	if(left_sensor<50) {
		low_left++;
	}else if(right_sensor<50) {
		low_right++;
	}else{
		low_left=0;
		low_right=0;
	}
	if(low_left>100){
		return LEFT_STUCK;
	}
	else if(low_right>100){
		return RIGHT_STUCK;
	}
    
    //ok to go forward
    if( front_sensor <= near_wall){
		//both sensors present - stay in middle
		/*if(right_sensor>side_near_wall && left_sensor>side_near_wall) {
			double error = left_sensor-right_sensor;//difference between right and left. negative means needs to turn left
			if(DEBUG2) {
				printf("STRAIGHT: %f,%f\n",right_sensor,error);
			}
			error/=500.0;
			
			if(error>1){error=1;}
			if(error<-1){error=-1;}
			return error;
        //only sees right wall
        }else*/ if(right_sensor>side_near_wall) {
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
        }else{
            return 0;
        }
	}
	//detects wall in front
	else {
        if(right_sensor>left_sensor) {
			return LEFT;
		}
		else {
			return RIGHT;
		}
    }
}
