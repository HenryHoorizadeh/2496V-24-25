//externing to make sure that these electrical component declarations are defined (the names can't be used more than once) and will be used multiple times in multiple files
//extern: external linkage

#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.h"

#ifndef ROBOTH
#define ROBOTH

//controller
extern pros::Controller con;

//rotation sensor
extern pros::Rotation roto;
extern pros::Rotation ODOMX;
extern pros::Rotation ODOMY;

//chassis motors
extern pros::Motor LF;
extern pros::Motor LB;
extern pros::Motor RF;
extern pros::Motor RB;
extern pros::Motor RM;
extern pros::Motor LM;

extern pros::Motor TEST;
extern pros::Motor TEST2;

//lift
extern pros::Motor LIFT;

//intake
extern pros::Motor INTAKE;
extern pros::Motor HOOKS;

//sensors
// extern pros::ADIEncoder encLeft;
// extern pros::ADIEncoder encRight;
// extern pros::ADIEncoder encMid;

//imu
extern pros::Imu imu;

//pneumatics
extern pros::ADIDigitalOut mogo;
extern pros::ADIDigitalOut scrapper;
extern pros::ADIDigitalOut intake;
extern pros::ADIDigitalOut hang;
//gps
// extern pros::Gps gps1;
// extern pros::c::gps_status_s_t gpsData;

//auton selector
extern pros::ADIDigitalIn selec;

extern pros::Optical OpticalC;

//vision
// extern pros::Vision vision;

#endif