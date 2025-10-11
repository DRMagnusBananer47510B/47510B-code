
#ifndef OPCONTROL_H
#define OPCONTROL_H


#include "EZ-Template/PID.hpp"
#include "pros/motors.hpp"
extern pros::Motor intake;
extern pros::Motor hood;
extern int intakeSpeed;
extern bool intakeOn;
extern bool hoodon;
void intaketoggle();
void hoodtoggle ();
extern ez::PID intakePID;
int intakeRun();


#endif
