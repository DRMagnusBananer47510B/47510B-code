
#include "EZ-Template/PID.hpp"
#include "opcontrol.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"
bool clawflip = false;
bool clawtilt = false;
bool claw = false;
ez::Piston clawflipper('d');
ez::Piston clawtilter('f');
ez::Piston clawer('g');
void clawtoggle(){
    claw = !claw;
    clawer.set(claw);
}
void clawflipRun(){
    clawflip = !clawflip;
    clawflipper.set(clawflip);
}
void clawtiltRun(){
    clawtilt = !clawtilt;
    clawtilter.set(clawtilt);
}
int liftSpeed = 600;
pros::MotorGroup lift({-9,20});
void liftRun(){
    while(true){
        if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
            lift.move(127)
        }
        else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
            lift.move(-127)
        }
        else{
            lift.move_voltage(0);
            lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        }
        pros::delay(10);
    }
}
// bool intakeOn = false;
// bool hoodon = false;
// int intakeSpeed = 600;
// bool load = false;
// bool middle = false;
// int now = 0;
// int clickDelay = 300;
// int hoodspeed = 600;
// bool stop = false;
// ez::Piston stopper('b');
// void stoptoggle(){ 
//     stop = !stop;
//     stopper.set(stop);
// }
// ez::Piston middlegoal('a');
// ez::Piston descore('c');
// bool push = true;

// ez::Piston loader ('e');
// ez::PID intakePID(1,0,0);
// pros::Motor intake (-20);
// pros::Motor hood (-14);
// void intaketoggle(){
//     intakeSpeed = 600;
//     intakeOn = !intakeOn;
//     hoodspeed = 600;
//     hoodon = !hoodon;
// }
// void loadRun(){
//  load = !load;
//  loader.set(load);
// }
// void descoreRun(){
//     push = !push;
//     descore.set(push);
// }

// int intakeRun(){
//     while (true){
//         if(intakeOn){
            
//             intake.move_velocity(-intakeSpeed);
            
//             hood.move_velocity(intakeSpeed);
//         }
//         else {
//             intake.move_voltage(0);
//           hood.move_voltage(0);
//         }

//         pros::delay(20);
//     }
// }
// void middlegoalscorer(){
// middle=!middle;
// middlegoal.set(middle);
// }
