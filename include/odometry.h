#include "api.h"
#include "main.h"

#ifndef ODOH
#define ODOH
//4.73388888889
#define FORWARD_OFFSET 4.4
#define SIDEWAYS_OFFSET 0
#define IMU_THRESHOLD 0.0001
#define HEADING_CUTOFF 0.6

extern void odometry();
extern void odometry2();
extern void driveToPoint (double xTarget, double yTarget, double perferredHeading);
extern void boomerang(double xTarget, double yTarget);
extern void setPosition(float xcoord, float ycoord, float heading);

extern double imu_pos_radians;
extern double x_pos;
extern double y_pos;

#endif