
#include "EZ-Template/PID.hpp"
#include "opcontrol.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"

bool intakeOn = false;
bool hoodon = false;
int intakeSpeed = 600;
ez::PID intakePID(1,0,0);
pros::Motor intake (20);
pros::Motor hood (-14);
void intaketoggle(){
    intakeOn = !intakeOn;
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
        }
        else {
            hood.move_voltage(0);
        
        }

        pros::delay(20);
    }
}
void hoodtoggle(){
    hoodon = !hoodon;
}
