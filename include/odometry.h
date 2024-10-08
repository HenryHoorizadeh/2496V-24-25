#include "api.h"
#include "main.h"

#ifndef ODOH
#define ODOH

#define FORWARD_OFFSET 0
#define SIDEWAYS_OFFSET 230
#define IMU_THRESHOLD 0.0001
#define HEADING_CUTOFF 100

extern void odometry();
extern void odometry2();
extern void driveToPoint (double xTarget, double yTarget, double perferredHeading);
extern void boomerang(double xTarget, double yTarget);

extern float x_pos;
extern float y_pos;

#endif