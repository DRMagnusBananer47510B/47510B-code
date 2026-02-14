
#include "EZ-Template/PID.hpp"
#include "opcontrol.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"

bool intakeOn = false;
bool hoodon = false;
int intakeSpeed = 300;
bool load = false;
bool middle = false;
int hoodspeed = 600;
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
            double output = intakePID.compute_error(intakeSpeed-intake.get_actual_velocity(), intake.get_actual_velocity());
            intake.move_velocity(output);
            pros::lcd::print(5, "Output: %f Velocity: %f", output, intake.get_actual_velocity());
        }
        else {
            intake.move_voltage(0);

        }

        if (hoodon){
            double output = intakePID.compute_error(intakeSpeed-hood.get_actual_velocity(), hood.get_actual_velocity());
            hood.move_velocity(output);
            pros::lcd::print(6, "Output: %f Velocity: %f", output, hood.get_actual_velocity());
            hood.move_velocity(hoodspeed);
        }
        else {
            hood.move_voltage(0);
    }
}
}
void hoodtoggle(){
    intakeSpeed = 600;
    hoodspeed = 600;
    hoodon = !hoodon;
}
void middlegoalscorer(){
middle=!middle;
middlegoal.set(middle);
}