
#include "EZ-Template/PID.hpp"
#include "opcontrol.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"

bool intakeOn = false;
bool hoodon = false;
int intakeSpeed = 600;
bool load = false;
bool middle = true;
int now = 0;
int clickDelay = 300;
int hoodspeed = 600;
bool stop = false;
ez::Piston stopper('b');
void stoptoggle(){ 
    stop = !stop;
    stopper.set(stop);
}
ez::Piston middlegoal('a');
ez::Piston descore('c');
bool push = false;

ez::Piston loader ('e');
ez::PID intakePID(1,0,0);
pros::Motor intake (-20);
pros::Motor hood (-14);
void intaketoggle(){
    intakeSpeed = 600;
    intakeOn = !intakeOn;
    hoodspeed = 600;
    hoodon = !hoodon;
}
void loadRun(){
 load = !load;
 loader.set(load);
}
void descoreRun(){
    push = !push;
    descore.set(push);
}

int intakeRun(){
    while (true){
        if(intakeOn){
            
            intake.move_velocity(-intakeSpeed);
            
            hood.move_velocity(intakeSpeed);
        }
        else {
            intake.move_voltage(0);
          hood.move_voltage(0);
        }

        pros::delay(20);
    }
}
void middlegoalscorer(){
middle=!middle;
middlegoal.set(middle);
}
