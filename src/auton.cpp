#include "api.h"
#include "auton.h"
#include "main.h"
#include "robot.h"
#include "pid.h"
#include "odometry.h"

using namespace std;
using namespace pros;

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or t
 * he VEX Competition Switch in the autonomous
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
    // LadyBrown.move(-127);
    // delay(500);
    // driveClamp(-500, 100);


    LadyBrown.move(127);
    HOOKS.move(-127);
    delay(500);
    HOOKS.move(127);
    driveStraight2(500);
    HOOKS.move(-127);
    driveTurn2(-90);
    mogoValues = true;
    driveClamp(-900, 100, 40);
    driveTurn2(0);
    driveStraightC(300);
    driveArcRF(45, 800, 2000);
    driveStraightC(425);
    driveArcLF(45, 500, 2000);
    driveStraight2(800);
    LBMacro = 1;
    driveStraight2(500, 80);
    driveTurn2(180);
    LBMacro = 2;
    //HOOKS.move(40);
    hookControl2 = true;
    driveStraightC(900);
    hookControl2 = false;
    HOOKS.move(-127);
    driveArcLF(90, 200, 2000);
    driveStraight2(100);
    HOOKS.move(127);
    LadyBrown.move(127);
    delay(800);
    driveStraight2(-500);
    
    

  } else if (atn == 1) {



    // ramp.move(-127);
    // driveStraight2(500);
    // driveTurn2(-90);
    // driveClamp(-500, 100);
    // driveTurn2(0);
    // driveStraight2(100);
    // driveTurn2(-90);
    // driveStraight2(125);
    // driveTurn2(35);
    // driveStraight2(350);
    // driveTurn2(180);
    // driveTurn2(-90);
    // driveStraight2(45);
    // driveStraight2()


  } else if (atn == 3) { 
    
  } else if (atn == 4) { 

  } else if(atn == 5) {

  } else if (atn == 6){
    
  }
}