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
    /*

    LadyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    LadyBrown.move(40);
    
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
    driveStraightC(425); //425
    driveArcLF(45, 500, 2000);
    driveStraight2(800);
    delay(450);
    LBMacro = 1;
    driveStraight2(500, 80);
    driveTurn2(5);
    driveStraight2(-1550); //-1600
    delay(450);
    LBMacro = 2;
    //HOOKS.move(40);
    hookControl2 = true;
    driveTurn2(90);
    hookControl2 = false;
    HOOKS.move(-127);
    LBMacro = 0;
    LadyBrown.move(0);
    driveStraight2(500);
    driveTurn2(90);
    //old hook control spot
    delay(1200);
    HOOKS.move(0);
    delay(100);
    HOOKS.move(-127);
    delay(400);


    chasMove(70, 70);
    delay(400);
    hookControl2 = true;
    for(int i = 0; i <= 800; i++){
      LBMacro = 3;
      LadyBrownMacro();
      delay(1);
    }
    hookControl2 = false;
    // LadyBrown.move(-127);
    // delay(800);
    driveStraight2(-650);
    LadyBrown.move(127);
    // second part
    HOOKS.move(-127);
    // mogo.set_value(true);
    // delay(200);
    //second part
    driveTurn2(180);
    driveStraight2(2100, 60);
    LadyBrown.move(40);
    driveTurn2(60);
    driveStraight2(500);
    driveTurn2(-20);
    driveStraight2(-850);
    mogo.set_value(false);
    mogoValues = false;

    */
    ///// third part
    LadyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    LadyBrown.move(40);
    driveTurn2(45);    
    driveStraightC(1000);
    HOOKS.move_relative(-500, 400);
    driveStraight2(500);
    driveStraight2(-300);
    driveTurn2(135);
    driveClamp(-1200, 150, 50);
    HOOKS.move(-127);
    driveTurn2(-135);
    driveStraight2(1200);

    
    

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

        // LadyBrown.move(-127);
    // delay(500);
    // driveClamp(-500, 100);

    // LadyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    // LadyBrown.move(40);
    // HOOKS.move(-127);
    // delay(500);
    // HOOKS.move(127);
    // driveStraight2(500);
    // HOOKS.move(-127);
    // driveTurn2(-90);
    // mogoValues = true;
    // driveClamp(-900, 100, 40);
    // driveTurn2(0);
    // driveStraightC(300);
    // driveArcRF(45, 800, 2000);
    // driveStraightC(425);
    // driveArcLF(45, 500, 2000);
    // driveStraight2(800);
    // delay(250);
    // LBMacro = 1;
    // driveStraight2(500, 80);
    // //lb1 old one
    // driveTurn2(180);
    // //old spot 
    // driveStraightC(800);
    // LBMacro = 2;
    // //HOOKS.move(40);
    // hookControl2 = true;
    // driveArcLF(90, 200, 2000);
    // driveStraight2(60);
    // hookControl2 = false;
    // HOOKS.move(-127);
    // LBMacro = 0;
    // LadyBrown.move(0);
    // delay(1200);
    // HOOKS.move(0);
    // delay(100);
    // HOOKS.move(-127);
    // delay(400);


    // chasMove(70, 70);
    // delay(400);
    // HOOKS.move(127);
    // LadyBrown.move(-127);
    // delay(800);
    // driveStraight2(-500);
    // driveTurn2(180);
    
  } else if (atn == 4) { 

  } else if(atn == 5) {

  } else if (atn == 6){
    
  }
}