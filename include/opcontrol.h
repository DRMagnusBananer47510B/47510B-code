
#ifndef OPCONTROL_H
#define OPCONTROL_H


#include "EZ-Template/PID.hpp"
#include "pros/motors.hpp"
extern pros::Motor intake;
extern int intakeSpeed;
extern bool intakeOn;
void intaketoggle();
extern ez::PID intakePID;
int intakeRun();

#endif
