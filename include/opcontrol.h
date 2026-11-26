
#ifndef OPCONTROL_H
#define OPCONTROL_H


#include "EZ-Template/PID.hpp"
#include "EZ-Template/piston.hpp"
#include "pros/motors.hpp"
// extern pros::Motor intake;
// extern pros::Motor hood;
// extern int intakeSpeed;
// extern bool intakeOn;
// extern bool hoodon;
// extern int hoodspeed;
// void intaketoggle();
// void hoodtoggle ();
// extern ez::PID intakePID;
// int intakeRun();
// extern ez::Piston middlegoal;
// extern bool middle;
// extern void middlegoalscorer();
// extern bool load;
// extern ez::Piston loader;
// extern void loadtoggle();
// extern void loadRun();
// extern ez::Piston dih;
// extern bool push;
// extern void descoreRun();
// extern void doubleclick();
// extern int now;
// extern int lastCLickTime;
// extern int clickDelay;
// extern ez::Piston stopper;
// extern bool stop;
// extern void stoptoggle();
extern bool clawflip;
extern bool clawtilt;
extern bool claw;
extern ez::Piston clawer;
extern void clawtoggle();
extern ez::Piston clawflipper;
extern ez::Piston clawtilter;
extern void clawflipRun();
extern void clawtiltRun();
extern int liftSpeed;
extern pros::MotorGroup lift;
extern void liftRun();




#endif
