#include "api.h"
#include "auton.h"
#include "main.h"
#include "robot.h"
#include "pid.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */


void autonomous() {



  
  //INDEX
    //AUTON 0: SKILLS
    //AUTON 1: blue right
    //AUTON 2: blue left
    //AUTON 3:red right
    //AUTON 4: red left
    //AUTON 5: elims

//111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111


  if (atn == 0) {

 //score preload, grab stake get reds back into under the middle hangbar
  } else if (atn == 1) {

    /*LIFT.move(30);
    driveStraight(-390);
    mogo.set_value(true);
    driveTurn2(-90);
    HOOKS.move(127);
    driveStraight(-400);
    driveStraight2(400);
    mogo.set_value(false);
    driveTurn2(-145);
    driveClamp(-1300, 400);*/

    //driveStraight2(-310);

    

     INTAKE.move(127);
     LIFT.move_relative(-1000, 100);
     INTAKE.move(-127);
     delay(400);
     driveStraight2(260);
     LIFT.move(127);
    delay(1000);
    driveClampS(-1400, 400, 72);
    driveTurn2(-110);
    INTAKE.move(127);
    HOOKS.move(127);
    driveStraight2(800);
    driveTurn2(160);

    


    // driveTurn2(-90);
    // driveStraight2(500);
    // INTAKE.move(300);
    // driveTurn2(30);
    // INTAKE.move(300);
    // driveStraight2(-300);
    // driveTurn2(30);
    //driveStraight2(-5000);
  //blue left rush rush rush
  } else if (atn == 2) { 
    driveStraight2(-2000);
    mogo.set_value(true);
    driveTurn2(45);
    INTAKE.move(300);
    driveStraight2(1000);
    INTAKE.move(300);

  //red right
  } else if (atn == 3) { 

  } else if (atn == 4) { 

  } else if(atn == 5) {
  
  } else if (atn == 6){
    
  }
  
}
//////////////////////////////ARCHIVE/////////////////////////////////////////////////////////////////////////////////////////////////////////
