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

 //score preload, grab stake get reds back into under the middle hangbar
  } else if (atn == 1) {

    // LIFT.move(30);
    // driveStraight(-390);
    // mogo.set_value(true);
    // driveTurn2(-90);
    // HOOKS.move(127);
    // driveStraight2(-310);
  //lift
    RingColor = 2;
    INTAKE.move(-127);
    LIFT.move_relative(-1000, 125);
    delay(500);
    driveStraight2(250);
    LIFT.move(127);
    delay(900);
    driveClampS(-1400, 400, 50);//-1400
    LIFT.move(0);


    driveTurn2(18);
    intake.set_value(true);
    INTAKE.move(127);
    driveClampS(1000, -100, 50); //900
    HOOKS.move(127);
    delay(200);
    intake.set_value(false);
    driveStraight2(-200);
    // delay(200);
    driveStraight2(-800);
    driveTurn2(-115);
    driveStraight2(450);
    driveTurn2(160); //150
    driveStraight2(400);
    driveTurn2(145);
    driveStraight2(-500);
    driveTurn2(160);//175
    driveStraight2(625);
    LIFT.move(-127);
    // driveArcLF(-90, 100, 1800);
    // driveStraight2(-1000);


    // driveStraight2(-1000);
    // driveTurn2(105);
    // driveStraight2(400);

    










    // driveTurn2(-115); //-110
    // INTAKE.move(127);
    // HOOKS.move(127);
    // driveStraight2(900);
    // driveTurn2(90);
    // INTAKE.move(127);
    // HOOKS.move(127);
    // driveStraight2(500);
    // driveTurn2(130);
    // driveStraight2(100);
    // INTAKE.move(127);
    // HOOKS.move(127);
    // driveTurn2(10);
    // driveStraight2(200);

///old athens code
    //  driveTurn2(-180);
    // INTAKE.move(127);
    // HOOKS.move(127);
    // driveStraight2(500);
    // driveTurn2(30);
    // driveStraight2(100);
    // INTAKE.move(127);
    // HOOKS.move(127);
    // driveTurn2(10);
    // driveStraight2(200);
    
    
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

    RingColor = 2;
    //setPosition(0,0, -147);
    INTAKE.move(-127);
    LIFT.move_relative(-1000, 125);
    delay(500);
    driveStraight2(250);
    LIFT.move(127);
    delay(900);
    driveClampS(-1500, 400, 50);//-1400
    LIFT.move(10);


    driveTurn2(-18);
    intake.set_value(true);
    INTAKE.move(127);
    driveStraightSlow(950, 70); //900 //50%
    HOOKS.move(127);
    delay(200);
    intake.set_value(false);
    driveStraight2(-350);

    driveTurn2(60);
    mogo.set_value(false);

    driveTurn2(140);
    HOOKS.move(0);
    driveStraight2(1400);
    driveTurn2(55);
    driveClampS(-275, 100, 25);
    INTAKE.move(127);
    HOOKS.move(127);



    // driveTurn2(60);
    // delay(500);
    // mogo.set_value(false);
    // driveStraight2(350);//350
    // delay(500);
    // driveTurn2(-20); //-10
    // driveStraight2(-1000);
    // driveTurn2(10);
    // driveClampS(-300, 100, 30);

    // driveArcLF(-2.75, 20000,3000);
    // driveArcLF(-40, 300,3000);
    // driveClampS(-10,10,50);
    
    // driveClampS(-1350,100,70);

    // driveStraightC(-150);
    // driveArcLF(-40, 350, 1800);
    // driveClampS(-650,200,70);


      

      //rush rush rush
      driveStraight2(700);
      INTAKE.move(300);
      driveTurn2(20);
      driveStraight2(700);
      INTAKE.move(0);
      scrapper.set_value(true);
      driveStraight2(-500);
      scrapper.set_value(false);
      driveTurn2(-70);
      driveStraight(-400);
      mogo.set_value(true);
      delay(500);
      driveTurn2(-30);
      driveStraight2(500);
      

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
      //not mirrored
    RingColor = 2;
    //setPosition(0,0, -147);
    INTAKE.move(-127);
    LIFT.move_relative(-1000, 125);
    delay(500);
    driveStraight2(250);
    LIFT.move(127);
    delay(900);
    driveClampS(-1500, 400, 50);//-1400
    LIFT.move(10);
    driveTurn2(18);
    intake.set_value(true);
    INTAKE.move(127);
    driveStraightSlow(950, 70); //900 //50%
    HOOKS.move(127);
    delay(200);
    intake.set_value(false);
    driveStraight2(-350);
    driveTurn2(-60);
    mogo.set_value(false);
    driveTurn2(-140);
    HOOKS.move(0);
    driveStraight2(1400);
    driveTurn2(-55);
    driveClampS(-275, 100, 25);
    INTAKE.move(127);
    HOOKS.move(127);

      // driveClamp(-1350, 400);
      // driveStraight2(200);
      // driveTurn2(-75);
      // driveClamp(-200, 170);
      // driveStraight2(200);
      // INTAKE.move(300);
      // LIFT.move(300);
      // driveStraight2(300);
  } else if (atn == 4) { 

    //awp red left
    RingColor = 2;
    INTAKE.move(-127);
    LIFT.move_relative(-1000, 125);
    delay(400);
    driveStraight2(250);
    LIFT.move(127);
    delay(1200);
    driveClampS(-1350, 400,60);
    LIFT.move(20);
    driveTurn2(110);
    INTAKE.move(127);
    HOOKS.move(127);
    driveStraight2(500);
    driveTurn2(-115);
    driveStraight2(550);
    driveTurn2(140);
    driveStraight2(300);
    driveTurn2(130);
    driveStraight2(300);
    driveTurn2(170);
    driveStraight2(-600);
    LIFT.move_relative(-1150, 125);
    driveTurn2(-90);
    driveStraight2(600);



        // driveArcLF(130, 600, 3000);
    // driveStraight2(600);

    // driveTurn2(180);
    // INTAKE.move(127);
    // HOOKS.move(127);
    // driveStraight2(500);
    // driveTurn2(-90);
    // driveStraight2(100);
    // INTAKE.move(127);
    // HOOKS.move(127);
    // driveTurn2(-10);
    // driveStraight2(200);

  } else if(atn == 5) {
//rush red right
driveStraight2(1100);
scrapper.set_value(true);
driveStraight2(-1000);

  
  } else if (atn == 6){
     RingColor = 2;
    //setPosition(0,0, -147);
    INTAKE.move(-127);
    LIFT.move_relative(-1000, 125);
    delay(500);
    driveStraight2(250);
    LIFT.move(127);
    delay(900);
    driveClampS(-1400, 400, 50);//-1400
    LIFT.move(0);


    driveTurn2(18);
    intake.set_value(true);
    INTAKE.move(127);
    driveStraightSlow(1000, 70); //900 //50%
    HOOKS.move(127);
    delay(200);
    intake.set_value(false);
    driveStraight2(-200);
    // delay(200);
    driveStraight2(-800);
    driveTurn2(-115); //-115
    driveStraight2(450);
    driveTurn2(155); //160 //150
    driveStraight2(400);
    driveTurn2(145);
    driveStraight2(-500);
    driveTurn2(175);//175
    driveStraight2(625);
    LIFT.move(-127);
    driveTurn2(55);
    driveStraight2(1000);
    // driveArcLF(-90, 150, 1800);
    // driveStraight2(-1000);
    // boomerang(300, -1000);
    //driveStraight2(-1000);
    // delay(200);
    // driveTurn2(-110);
    // driveStraight2(1000);
  }
}