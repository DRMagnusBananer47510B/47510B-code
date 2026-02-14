
#ifndef OPCONTROL_H
#define OPCONTROL_H


#include "EZ-Template/PID.hpp"
#include "EZ-Template/piston.hpp"
#include "pros/motors.hpp"
extern pros::Motor intake;
extern pros::Motor hood;
extern int intakeSpeed;
extern bool intakeOn;
extern bool hoodon;
extern int hoodspeed;
void intaketoggle();
void hoodtoggle ();
extern ez::PID intakePID;
int intakeRun();
extern ez::Piston middlegoal;
extern bool middle;
extern void middlegoalscorer();
extern bool load;
extern ez::Piston loader;
extern void loadtoggle();
extern void loadRun();
extern ez::Piston descore;
extern bool push;
extern void descoreRun();




#endif