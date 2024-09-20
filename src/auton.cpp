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

    // LIFT.move(30);
    // driveStraight(-390);
    // mogo.set_value(true);
    // driveTurn2(-90);
    // HOOKS.move(127);
    // driveStraight2(-310);
  //lift
    INTAKE.move(-127);
    LIFT.move_relative(-1000, 125);
    delay(400);
    driveStraight2(250);
    LIFT.move(127);
    delay(1200);
    driveClampS(-1350, 400,60);
    LIFT.move(0);
    driveTurn2(-110);
    INTAKE.move(127);
    HOOKS.move(127);
    driveStraight2(500);
    driveTurn2(-180);
    INTAKE.move(127);
    RingColor = 1;
    HOOKS.move(127);
    driveStraight2(500);
    driveTurn2(30);
    driveStraight2(100);
    INTAKE.move(127);
    HOOKS.move(127);
    driveTurn2(10);
    driveStraight2(200);
    
    
  //intake score
      // driveTurn2(-90);
      // driveStraight2(500);
      // INTAKE.move(300);
      // driveTurn2(30);
      // INTAKE.move(300);
      // driveStraight2(-300);
      // driveTurn2(30);
      // driveStraight2(-5000);
    //blue left rush rush rush
    } else if (atn == 2) { 
      driveStraight2(2200);
      scrapper.set_value(true);
      driveTurn2(45);
      driveStraight(300);
      INTAKE.move(300);
      driveStraight2(1000);
      INTAKE.move(300);
      mogo.set_value(false);
      driveTurn2(75);
      driveStraight2(-1000);
      mogo.set_value(true);
      driveTurn2(-50);
      driveStraight2(1100);
      INTAKE.move(-200);
      driveStraight2(100);
      INTAKE.move(300);
    //red right
    } else if (atn == 3) { 
      driveClamp(-1350, 400);
      driveStraight2(200);
      driveTurn2(-75);
      driveClamp(-200, 170);
      driveStraight2(200);
      INTAKE.move(300);
      LIFT.move(300);
      driveStraight2(300);
  } else if (atn == 4) { 

  } else if(atn == 5) {
  
  } else if (atn == 6){
    
  }
}