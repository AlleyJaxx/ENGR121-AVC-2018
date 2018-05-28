#include <stdio.h>
#include "E101.h"
#include "time.h"
#include "img_process.h"

//bools
bool gate_down=false;
bool seen_gate=false;
bool wait_gate = false;

//sensors
double front_sensor;
double left_sensor;
double right_sensor;
double front_noise;
double left_noise;
double right_noise;
int frames = 0;

int right_stuck = 0;
int left_stuck = 0;

//sensor value
const double near_wall =210;
const double side_near_wall=400;
const double hug_right_threshold=500;
bool DEBUG2 = true;
    
bool check_red2()
{
	take_picture();
	
	int r = get_pixel(220,160,0);
	int g = get_pixel(220,160,1);
	int b = get_pixel(220,160,2);
	/*if(DEBUG2) {
		printf("%d,%d,%d\n",r,g,b);
	}*/
	return (r>200 && g<180 && b<180);
}

void calc_sensor(double* sensor, double* noise, int read)
{
	double min = 1024;
	double max = 0;
	double total = 0;
	for(int i = 0;i<10;i++) {
		double reading = (double)read_analog(read);
		total+=reading;
		if(reading>max) max = reading;
		if(reading<min) min = reading;
	}
	
	*sensor = total/10.0;
	*noise = max-min;
}

void sensor_read() {
	calc_sensor(&front_sensor,&front_noise, 0);
	calc_sensor(&right_sensor,&right_noise, 2);
	calc_sensor(&left_sensor,&left_noise, 1);
	
}

int waitForWallDetect() {
	sensor_read();

	if(right_sensor>side_near_wall) {
		return 1;
	}else if(left_sensor>side_near_wall) {
		return -1;
	}else{
		return 0;
	}
}

double quadrant4_turn(){
    sensor_read();
    if(DEBUG2) {
        printf("%f,%f | %f,%f | %f,%f\n",front_sensor,front_noise,left_sensor,left_noise,right_sensor,right_noise);
    }
	frames++;
    //wait at gate
    if((check_red2() || wait_gate) &&  !seen_gate && frames>200){
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
	
	/*if(right_sensor<300&&left_sensor<150&& left_sensor>100 && front_sensor>100) {
		right_stuck++;
		if(right_stuck>20) {
			return STUCK;
		}
	}else{
		right_stuck = 0;
	}
	 if(left_sensor<300&&right_sensor<150&& right_sensor>100 && front_sensor>100) {
                left_stuck++;
                if(left_stuck>20) {
                        return STUCK;
                }
        }else{
                left_stuck = 0;
        }*/

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
            //return STUCK;
        }
	}
	//detects wall in front
	else {
	double value = (double)front_sensor/500.0;
        if(right_sensor>left_sensor) {
			return -value;
		}
		else {
			return value;
		}
    }
}
