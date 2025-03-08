//constructors for everything electrical

#include "api.h"
//#include "auton.h"
#include "main.h"
#include "robot.h"
#include "pros/motors.h"





// 2496v
#define LF_PORT 20
#define LM_PORT 18
#define LB_PORT 19
#define RF_PORT 15
#define RM_PORT 16
#define RB_PORT 17
#define IMU_PORT 2
#define HOOKS_PORT 14
#define ROTO_PORT 1
#define ODOMX_PORT 7
#define ODOMY_PORT 2
#define TEST_PORT 3
#define TEST_PORT2 14
#define LDB_PORT 13
#define OPTICAL_PORT 3




//rotation sensor
pros::Rotation roto(ROTO_PORT);
pros::Rotation ODOMX(ODOMX_PORT);
pros::Rotation ODOMY(ODOMY_PORT);

pros::Motor LF (LF_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor LM (LM_PORT, pros::E_MOTOR_GEARSET_06, false);
pros::Motor LB (LB_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor RF (RF_PORT, pros::E_MOTOR_GEARSET_06, false);
pros::Motor RM (RM_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor RB (RB_PORT, pros::E_MOTOR_GEARSET_06, false);

pros::Motor TEST (TEST_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor TEST2 (TEST_PORT2, pros::E_MOTOR_GEARSET_06, false);

//lady brown
pros::Motor LadyBrown (LDB_PORT, pros::E_MOTOR_GEARSET_06, false);




//hooks
pros::Motor HOOKS (HOOKS_PORT, pros::E_MOTOR_GEARSET_06, false);

//pneumatics
    //Mogo
    pros::ADIDigitalOut mogo ('A', false);

    //doinker
    pros::ADIDigitalOut doinker ('H', false);
    
    pros::ADIDigitalOut doinkerClamp('E', false);

    //pistoned intake
    pros:: ADIDigitalOut intake ('G', false);

    //auton selector
    pros::ADIDigitalIn selec ('F');

    //hang
    pros::ADIDigitalOut hang ('D', false);

    pros::ADIDigitalOut colorSorter('C', false);



//sensors
// pros::ADIEncoder encLeft ({{1, 1, 2}, false});
// pros::ADIEncoder encRight ({{1, 3, 4}, false});
// pros::ADIEncoder encMid ({{1, 5, 6}, false});

pros::Imu imu (IMU_PORT);

//controller
pros::Controller con (pros::E_CONTROLLER_MASTER);

//optical sensor
pros::Optical OpticalC (OPTICAL_PORT);


//gps
// #define X_OFFSET .225
// #define Y_OFFSET .223
// #define X_INITIAL 1.54
// #define Y_INITIAL 1.14
// #define HEADING_INITIAL 90
// pros::Gps gps1(GPS_PORT, X_INITIAL, Y_INITIAL, HEADING_INITIAL, X_OFFSET, Y_OFFSET);
// pros::c::gps_status_s_t gpsData;

// pros::Vision vision (18);