
#include "EZ-Template/PID.hpp"
#include "opcontrol.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"

bool intakeOn = false;
int intakeSpeed = 600;
ez::PID intakePID(1,0,0);
pros::Motor intake (15);
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
        pros::delay(20);
    }
}