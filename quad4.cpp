#include "E101.h"
#include <stdio.h>

int main(){

//constants that we need to work out
int side_threshold  = 400;//distance to detect the right wall 
int hug_right_threshold = 610;//robot will try to keep this distance from the right wall
int forward_threshold = 250;// distant to wall before bot turns/stop. Will continue straight until this threshold is reached
	
	init();
	
while (true){
	double distance_to_front = read_analog(0);
	double distance_to_left = read_analog(1);
	double distance_to_right_front = read_analog(2);
	double distance_to_right_back = read_analog(3);
	
	
	//detect gap in right wall
	while (double distance_to_right < side_threshold){
		distance_to_right = distance_to_right - hug_right_threshold; //no wall on the right
		turn(0.3);// turn right
	}	

	//hug left wall if right wall not detected
	if (int distance_to_left < side_threshold){
		distance = hug_right_threshold - distance to left;
	}


	//go straight if no walls detected
	if (int distance to right 


	return 0 // go straight

}


//Wait until front of robot is close enough to wall:

	//gap on right
	//turn right
	//wall on front. gap on left. 
	//turn left
	//forward until detects front wall. no wall on left. 
	//turn left. 
	//detect red line 
    //wait. detect forward
    //once wall down. wait till dont see. go. 
	//forward until detects front wall. no wall on left.
	//turn left
	//forward
    //Dead end - must be the end - stop


//other variables
double turn //at an intersection will turn with this value
some timer variable for keeping track of how long a right angle turn has occured

//loop (returns turn amount for movement)

//in the middle of turning - wait until enough time has passed
if turn=0
    if timer < some value
        return turn // skips next code
    else
        set turn to 0

//check once it close enough to a wall to turn, then use the left/right sensors to tell what to do
if front sensor distance < forward_threshold
    if right sensor distance > side_threshold
        set turn to some value >1
        start timer
        return turn
    else if left sensor distance > side_threshold
        set turn to some value <1
        start timer
        return turn
    else stop (return some value that will make it stop)
//hug right wall
else


