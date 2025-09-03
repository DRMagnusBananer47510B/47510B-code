
#ifndef _OPCONTROL_H_
#define _OPCONTROL_H_
#include "pros/imu.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
extern pros::IMU imu;
extern pros::Controller master;
extern pros::Motor intake;
extern pros::MotorGroup left_mg;
extern pros::MotorGroup right_mg;
extern pros::Motor lf;
extern pros::Motor lm;
extern pros::Motor lb;
extern pros::Motor rf;
extern pros::Motor rm;
extern pros::Motor rb;
extern bool intaketoggle;
class PID {
public:
  double kp;
  double ki;
  double kd;
  double integral;
  double prevError;
  PID(double p, double i, double d) {
    kp = p;
    ki = i;
    kd = d;
    integral = 0;
    prevError = 0;
  }
  double calculate(double target, double current) {
    double error = target - current;
    integral += error;
    double derivative = error - prevError;
    prevError = error;
    return (kp * error) + (ki * integral) + (kd * derivative);
  }
};
extern void turnToAngle(double targetAngle);
extern PID turnPID;

#endif // _OPCONTROL_H_