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

 //back into the stake grab and turn go into blue and red stack, grab blue; 
 //push middle stacks over, score on high stake and back off to positive corner
  } else if (atn == 1) {
    driveStraight(-170);
    mogo.set_value(true);
    driveTurn(90);
    driveStraight(30);
    INTAKE.move(100);


  } else if (atn == 2) { 

  } else if (atn == 3) { 

  } else if (atn == 4) { 

  } else if(atn == 5) {
  
  } else if (atn == 6){
    
  }
  
}
//////////////////////////////ARCHIVE/////////////////////////////////////////////////////////////////////////////////////////////////////////
