#include "api.h"
#include "main.h"
#include "okapi/api.hpp"
#include "pros/api_legacy.h"

//header guards
#ifndef PIDH
#define PIDH

extern void setPosition(float xcoord, float ycoord, float heading);
extern void resetEncoders();
extern void setConstants(double kp, double ki, double kd);
extern void setConstants2(double kp, double ki, double kd);
extern double calcPID(double target, double input, int integralKi, int maxIntegral, bool slewOn);
extern double calcPID2(double target, double input, int integralKi, int maxIntegral, bool slewOn);
extern double calcPIDlift(double target, double input, int integralKi, int maxIntegral, double bias);
extern void driveStraight(int target);
extern void driveStraight2(int target, int speed = 100);
extern void driveClamp(int target, int clampDistance, int speed = 100);
extern void driveStraightC(int target);
extern void driveTurn(int target);
extern void driveTurn2(int target);
extern void driveTurnT(int target);
extern void chasMove(int left, int right);
extern void driveArcL(double theta, double radius, int timeout);
extern void driveArcLF(double theta, double radius, int timeout);
extern void driveArcR(double theta, double radius, int timeout);
extern void driveArcRF(double theta, double radius, int timeout);
extern void ColorSort();
extern void hooks(int speed);
extern void intake2(int speed);
extern void stall();
extern void LadyBrownMacro();

extern int time2; 
extern float error;
extern float error2;
extern int integral;
extern int ColorCount;
extern double totalError;
extern bool longValues;
extern bool mogoValues;
extern bool stallProtection;
extern bool sreverse;
extern bool stalled;
extern float view;
extern int stallTime;
extern bool hookControl2;
extern int LBMacro;

//tune straight constants here: setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
#define STRAIGHT_KP 0.4 // 1 //0.7
#define STRAIGHT_KI 0.01 // 0.001 //0.1
#define STRAIGHT_KD 4.25 // 1 //8

//tune straight integral-specific here: voltage = calcPID(target, encoderAvg, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL);
#define STRAIGHT_INTEGRAL_KI 40
#define STRAIGHT_MAX_INTEGRAL 14.5

#define STRAIGHT_KPM 0.5 // 1 //0.7
#define STRAIGHT_KIM 0.01 // 0.001 //0.1
#define STRAIGHT_KDM 7 // 1 //8

//tune to make heading correction more or less senstive 
#define HEADING_CORRECTION_KP 0

//tune turn constans here: setConstants(TURN_KP, TURN_KI, TURN_KD);
#define TURN_KP 5//5.25//8.75
#define TURN_KI 0 //0.125//0.115
#define TURN_KD 58 //38 //105 //70

//tune turn integral-specific here: voltage = calcPID(target, position, TURN_INTEGRAL_KI, TURN_MAX_INTEGRAL);
#define TURN_INTEGRAL_KI 30
#define TURN_MAX_INTEGRAL 25

#define TURNT_KP 10 //3
#define TURNT_KI 0 //
#define TURNT_KD 70 //30

//tune turn integral-specific here: voltage = calcPID(target, position, TURN_INTEGRAL_KI, TURN_MAX_INTEGRAL);
#define TURNT_INTEGRAL_KI 30
#define TURNT_MAX_INTEGRAL 25

//tune to make headding correction in arcturns more or less sensitive 
#define ARC_CORRECTION_KP 10

#define HEADING_KP 5 //5.25//8.75 //15/////////15
#define HEADING_KI 0 //0.125//0.115
#define HEADING_KD 100 //38 //105 //70 //100 //180///////////////400

#define HEADING_KP2 20 //5.25//8.75 //15
#define HEADING_KI2 0 //0.125//0.115
#define HEADING_KD2 500 //38 //105 //70 //100 //180

#define HEADING_INTEGRAL_KI 0
#define HEADING_MAX_INTEGRAL 0

#define ARC_HEADING_KP 20 //5.25//8.75 //40 //40
#define ARC_HEADING_KI 0 //0.125//0.115
#define ARC_HEADING_KD 30 //38 //105 //70 //40

#define ARC_HEADING_INTEGRAL_KI 0
#define ARC_HEADING_MAX_INTEGRAL 0

//tune straight constants here: setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
#define LIFT_KP 1 // 1
#define LIFT_KI 0 // 0.001
#define LIFT_KD 0  // 1

#define LIFT_KP2 0.125 // 1
#define LIFT_KI2 0 // 0.001
#define LIFT_KD2 0.5  // 1

//tune straight integral-specific here: voltage = calcPID(target, encoderAvg, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL);
#define LIFT_INTEGRAL_KI 40
#define LIFT_MAX_INTEGRAL 14.5




#endif