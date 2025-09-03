#include "opcontrol.h"
#include "pros/imu.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor intake(15);
pros::Motor lf(1);
pros::Motor lm(16);
pros::Motor lb(19);
pros::Motor rf(-10);
pros::Motor rm(-5);
pros::Motor rb(-6);
pros::IMU imu(7);
pros::MotorGroup left_mg({1, 16, 19}); // Creates a motor group with forwards
                                       // ports 1 & 3 and reversed port 2
pros::MotorGroup right_mg({-10, -5, -6});
bool intaketoggle = false;

PID turnPID(2.5, 0.01, 0.1); // Example PID values for turning

void turnToAngle(double targetAngle) {
  left_mg.move(turnPID.calculate(targetAngle, imu.get_heading()));
  right_mg.move(turnPID.calculate(targetAngle, imu.get_heading()));
};