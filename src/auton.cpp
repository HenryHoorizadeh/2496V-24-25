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
    HOOKS.tare_position();    
    LadyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    LadyBrown.move(10);
    HOOKS.move(-127);
    delay(500);
    HOOKS.move(127);
    //LBMacro = 4;
    driveStraight2(500);
    HOOKS.move(-127);
    driveTurn2(-90);
    //mogoValues = true;
    driveClamp(-900, 100, 40);
    mogoValues = true;
    driveTurn2(0);
    driveStraightC(500); //500
    driveArcRF(26, 800, 2000); //26
    driveStraight2(2200);
    // for(int i = 0; i <= 5000; i++){
    //  if (i % 150 == 0){
    //     con.print(2, 0, "imu: %f        ", float(imu.get_heading()));
    //   } 
    //   delay(1);
    // }

    delay(150); //450
    LBMacro = 1;
    driveStraight2(475, 80);//500
    //LBMacro = 1;
    driveTurn2(20);//25
    driveStraight2(-1700); //-1800
    delay(150);
    LBMacro = 2;
    //HOOKS.move(40);
    hookControl2 = true;
    driveTurn2(90);
    hookControl2 = false;
    HOOKS.move(-127);
    // LBMacro = 0;
    // LadyBrown.move(0);
    driveStraight2(600); //500
    driveTurn2(90);
    //old hook control spot
    delay(400); //500
    HOOKS.move(0);
    delay(50); //100
    HOOKS.move(-127);
    delay(100); //200


    chasMove(100, 100);
    delay(400); //400
    HOOKS.tare_position();   
    hookControl2 = true;
    for(int i = 0; i <= 800; i++){
      LBMacro = 3;
      LadyBrownMacro();
      delay(1);
    }
    hookControl2 = false;
    // LadyBrown.move(-127);
    // delay(800);
    driveStraight2(-550); //-650
    LBMacro = 0;
    LadyBrown.move(127);
    //LBMacro = 4;

    //LadyBrown.move(127);
    // second part
    HOOKS.move(-127);
    // mogo.set_value(true);
    // delay(200);
    //second part
    driveTurn2(180);
    driveStraight2(2100, 40);
    LadyBrown.move(40);
    driveTurn2(60);
    driveStraight2(450);//650
    driveTurn2(-45);
    driveStraight2(-300);
    mogo.set_value(false);
    mogoValues = false;
    HOOKS.move(127);
    driveTurn2(-45);
    driveStraight2(150);
    driveTurn2(91);
    longValues = true;
    driveClamp(-3225, 100, 50);
    longValues = false;
    mogoValues = true;
    HOOKS.move(-127);
    driveStraight2(125);
    // driveTurn2(0);

    //////////////////////////////////////////////////////////////

    mogoValues = true;
    





    ////////////////old 2nd half
    driveTurn2(0);
    driveStraightC(500); //500
    driveArcLF(26, 800, 2000); //26
    driveStraight2(2200);
    // for(int i = 0; i <= 5000; i++){
    //  if (i % 150 == 0){
    //     con.print(2, 0, "imu: %f        ", float(imu.get_heading()));
    //   } 
    //   delay(1);
    // }

    delay(150); //450
    LBMacro = 1;
    driveStraight2(475, 80);//500
    //LBMacro = 1;
    driveTurn2(-20);//25
    driveStraight2(-1700); //-1800
    delay(150);
    LBMacro = 2;
    //HOOKS.move(40);
    hookControl2 = true;
    driveTurn2(-90);
    hookControl2 = false;
    HOOKS.move(-127);
    // LBMacro = 0;
    // LadyBrown.move(0);
    driveStraight2(600); //500
    driveTurn2(-90);
    //old hook control spot
    delay(400); //500
    HOOKS.move(0);
    delay(50); //100
    HOOKS.move(-127);
    delay(100); //200
    
    HOOKS.move(40);
    chasMove(100, 100);
    delay(400); //400
    hookControl2 = true;
    for(int i = 0; i <= 800; i++){
      LBMacro = 3;
      LadyBrownMacro();
      delay(1);
    }
    hookControl2 = false;
    // LadyBrown.move(-127);
    // delay(800);
    driveStraight2(-550); //-650
    LBMacro = 0;
    LadyBrown.move(127);
    //LBMacro = 4;

    //LadyBrown.move(127);
    // second part
    HOOKS.move(-127);
    // mogo.set_value(true);
    // delay(200);
    //second part
    driveTurn2(180);
    driveStraight2(2100, 40);
    LadyBrown.move(40);
    driveTurn2(-60);
    driveStraight2(450);//650
    driveTurn2(45);
    driveStraight2(-300);
    mogo.set_value(false);
    mogoValues = false;
//////////////old 2nd half



    mogoValues = false;
    HOOKS.move(127);
    driveTurn2(46);
    driveStraightR(3000, 70);





    /*
    driveStraightC(300);
    driveArcLF(15, 800, 2000);
    driveStraight2(2200);
    delay(450);
    LBMacro = 1;
    driveStraight2(800, 80);
    driveTurn2(-5); //-5
    driveStraight2(-1700); //-1750
    delay(450);
    LBMacro = 2;
    //HOOKS.move(40);
    hookControl2 = true;
    driveTurn2(-90);
    hookControl2 = false;
    HOOKS.move(-127);
    LBMacro = 0;
    LadyBrown.move(0);
    driveStraight2(500);
    driveTurn2(-90);
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
    driveStraight2(2100, 40);
    LadyBrown.move(40);
    driveTurn2(-60);
    driveStraight2(650);
    driveTurn2(20);
    driveStraight2(-450);
    mogo.set_value(false);
    mogoValues = false;
    HOOKS.move(127);

    */

    



    
    ///// third part
    color = 1;
    LBMacro = 0;
    LadyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    LadyBrown.move(30);
    // driveTurn2(45);
    HOOKS.move_relative(300, 600);
    driveStraight2(1300);
    HOOKS.move_relative(-450, 400);
    driveStraight2(400);
    driveTurn2(115);
    driveClamp(-1500, 150, 50);
    HOOKS.move(-127);
    driveTurn2(-140);
    driveStraight2(1300);
    driveTurn2(-40);
    driveStraightC(600);
    driveArcRF(40, 300, 1800);
    doinker.set_value(true);
    driveStraight2(250, 70);
    driveTurn2(-60);
    driveStraight2(550);
    delay(400);
   // driveTurn2(-170);
    driveTurn2(135); //120
    doinker.set_value(false);
    driveStraight2(-400);
    mogo.set_value(false);
    HOOKS.move(127);
    driveTurn2(135);
    driveStraightC(700);
    HOOKS.move(-127);
    driveArcLF(90, 300, 2000);
    driveStraightC(700);
    driveArcRF(30, 300, 2000);
    HOOKS.move(0);
    driveStraight2(2500);
    driveTurn2(40);
    LBMacro = 3;
    driveStraight2(-2700, 60);
    LBMacro = 0;
    LadyBrown.move(127);



    





    // LBMacro = 0;
    // LadyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    // LadyBrown.move(127);
    // driveTurn2(45);
    // LadyBrown.move(40);
    // HOOKS.move(0);
    // driveStraightC(3200);
    // driveArcLF(115, 250, 1800);
    // driveStraightC(1000);
    // driveArcRF(30, 250, 1900);
    // driveArcLF(30, 250, 1900);
    // driveStraight2(900);
    // driveStraight2(-1600);
    // driveTurn2(65);
    // driveStraight2(2400);



    // driveStraightC(1500);
    // HOOKS.move_relative(-400, 400);
    // driveStraight2(500);
    // driveStraight2(-300);
    // driveTurn2(135);
    // driveClamp(-1200, 150, 50);
    // HOOKS.move(-127);
    // driveTurn2(-105);
    // driveStraight2(-2600);
    // mogo.set_value(false);
    // driveStraight2(500);
    // driveTurn2(75);
    // driveStraight2(1500);




    // driveTurn2(-135);
    // driveStraight2(1200);
    // driveTurn2(-75);
    // driveStraightC(400);
    // driveArcLF(120, 90, 1800);
    // driveStraight2(500);


    
    



    /*
    // LadyBrown.move(-127);
    // delay(500);
    // driveClamp(-500, 100);
    

    LadyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    //LadyBrown.move(40);
    HOOKS.move(-127);
    delay(500);
    HOOKS.move(127);
    LBMacro = 4;
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
    delay(150); //450
    LBMacro = 1;
    driveStraight2(500, 80);
    driveTurn2(5);
    driveStraight2(-1550); //-1600
    delay(150);
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
    delay(500); //1200
    HOOKS.move(0);
    delay(100);
    HOOKS.move(-127);
    delay(200); //400


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
    LBMacro = 4;
    //LadyBrown.move(127);
    // second part
    HOOKS.move(-127);
    // mogo.set_value(true);
    // delay(200);
    //second part
    driveTurn2(180);
    driveStraight2(2100, 40);
    LadyBrown.move(40);
    driveTurn2(60);
    driveStraight2(650);
    driveTurn2(-45);
    driveStraight2(-500);
    mogo.set_value(false);
    mogoValues = false;
    HOOKS.move(127);

    driveStraight2(500);
    driveTurn2(90);
    driveClamp(-2700, 100, 40);
    HOOKS.move(-127);
    driveStraight2(225);
    driveTurn2(0);

    //////////////////////////////////////////////////////////////

    driveStraightC(300);
    driveArcLF(45, 800, 2000);
    driveStraightC(800); //425
    driveArcRF(45, 500, 2000);
    driveStraight2(900);
    delay(450);
    LBMacro = 1;
    driveStraight2(800, 80);
    driveTurn2(-5);
    driveStraight2(-1750); //-1600
    delay(450);
    LBMacro = 2;
    //HOOKS.move(40);
    hookControl2 = true;
    driveTurn2(-90);
    hookControl2 = false;
    HOOKS.move(-127);
    LBMacro = 0;
    LadyBrown.move(0);
    driveStraight2(500);
    driveTurn2(-90);
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
    driveStraight2(2100, 40);
    LadyBrown.move(40);
    driveTurn2(-60);
    driveStraight2(650);
    driveTurn2(20);
    driveStraight2(-450);
    mogo.set_value(false);
    mogoValues = false;
    HOOKS.move(127);



    
    ///// third part
    LBMacro = 0;
    LadyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    LadyBrown.move(127);
    driveTurn2(45);
    LadyBrown.move(40);
    HOOKS.move(0);
    driveStraightC(3200);
    driveArcLF(135, 150, 1800);
    driveStraight2(2400);
    driveStraight2(-1500);
    driveTurn2(-65);
    driveStraight2(2400);



    // driveStraightC(1500);
    // HOOKS.move_relative(-400, 400);
    // driveStraight2(500);
    // driveStraight2(-300);
    // driveTurn2(135);
    // driveClamp(-1200, 150, 50);
    // HOOKS.move(-127);
    // driveTurn2(-105);
    // driveStraight2(-2600);
    // mogo.set_value(false);
    // driveStraight2(500);
    // driveTurn2(75);
    // driveStraight2(1500);




    // driveTurn2(-135);
    // driveStraight2(1200);
    // driveTurn2(-75);
    // driveStraightC(400);
    // driveArcLF(120, 90, 1800);
    // driveStraight2(500);
*/

    
    

  } else if (atn == 1) {
  ////Red Left Ring
  LadyBrown.move(-127);
  driveStraight2(250);
  delay(700);
  LBMacro = 4;
  driveClamp(-1600, 150, 80);//1550
  HOOKS.move(-127);
  driveTurn2(160);
  driveStraightC(225); //275
  driveArcLF(39, 700, 2500);
  driveStraight2(300);
  driveStraight2(-600);
  driveArcLF(35, 250, 2500);
  driveTurn2(0);
  driveStraight2(300);
  driveTurn2(-34);
  intake.set_value(true);
  driveStraight2(1550, 60);
  intake.set_value(false);
  delay(300);
  driveStraight2(-300);
  driveTurn2(-110);
  driveStraight2(500);


    /*wallstake
    mogo.set_value(false);
    driveTurn2(0);
    driveStraight2(700);
    HOOKS.move(0);
    driveTurn2(120);
    driveStraight2(-500);
    driveTurn2(-150);
    driveStraight2(-200);
    */

    // driveTurn2(90);
 
    // driveStraight2(900);
    // driveStraight2(-300);
    // driveTurn2(-70);
    // driveStraight(600);
    // driveStraight2(-300);




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


  } else if (atn == 2) { 

    //red right rush mogo
    // HOOKS.move(-127);
    // driveClampD(1600, 200);
    color = 0;
    LadyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    LBMacro = 4;
    doinker.set_value(true);
    driveClampD(1600, 250, 1000);
    HOOKS.move(-5);
    driveStraight(-900);
    doinkerClamp.set_value(false);
    driveStraight2(-100);
    doinker.set_value(false);
    driveTurn2(-160);
    driveClamp(-800, 150, 60);
    HOOKS.move(-127);
    driveTurn2(-155);
    intake.set_value(true);
    driveArcLF(35, 2000, 9000);
    // driveStraight2(500);
    
    driveStraight2(2500);
    intake.set_value(false);
    driveStraight2(-1500);
    driveTurn2(-117);
    mogo.set_value(false);
    mogoValues = false;
    longValues = true;
    driveStraight2(1675);// why is this wiggly..
    longValues = false;
    LBMacro = 3;
    delay(2000);
  driveStraight2(-350);
  driveTurn2(-50);
  intake.set_value(true);
  HOOKS.move(-20);
  driveStraight2(400);
  intake.set_value(false);//i try to arc at the end but didnt work
  


    // doinker.set_value(true);
    // driveClampD(1600, 200);
    // driveStraight(-900);
    // doinkerClamp.set_value(false);
    // driveStraight2(-100);
    // doinker.set_value(false);
    // driveTurn2(-170);
    // driveClamp(-800, 150, 60);
    // HOOKS.move(-127);


    /*
    LBMacro = 4;
    driveStraightC(-875);
    driveArcLF(-30, 200, 2000);
    driveClamp(-910, 150);
    HOOKS.move(-127);
    driveStraight2(300);
    driveTurn2(65);
    mogo.set_value(false);
    driveStraight2(100);
    driveTurn2(-115);
    driveClamp(-700, 150, 60);
    driveTurn2(-65);
    driveStraight2(1000);
    driveTurn2(160);
    driveStraight2(-700);
    mogo.set_value(false);
    driveStraight2(700);
    driveTurn2(0);

    // driveTurn2(-40);
    // driveStraight2(1800);
    // intake.set_value(true);
    // driveArcRF(5, 1000, 1800);




    //old tworing
    // driveTurn2(-45);
    // driveStraight2(300);
    // driveTurn2(0);
    // delay(300);
    // mogo.set_value(false);
    // driveTurn2(-88);
    // driveClamp(-900, 150, 70);
    // intake.set_value(true);
    // driveTurn2(-45);
    // driveStraight2(1500);


    //old stuff
    // driveTurn2(41);
    // driveStraight2(975);
    // intake.set_value(false);
    // delay(300);
    // driveStraight2(-300);
    // driveTurn2(125);
    // delay(1000);
    // HOOKS.move(0);
    // driveStraight2(400);

    // driveClamp(-2000, 150);
    // HOOKS.move(-127);
    // driveTurn2(-15);
    // driveStraight2(500);
    // delay(300);
    // mogo.set_value(false);
    // driveTurn2(-105);




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

    */
    
  } else if (atn == 3) { 

    //blu left mogo
    LBMacro = 4;
    driveStraightC(-875);
    driveArcRF(-30, 200, 2000);
    driveClamp(-910, 150);
    HOOKS.move(-127);
    driveStraight2(300);
    driveTurn2(45);
    driveStraight2(300);
    driveTurn2(0);
    delay(300);
    mogo.set_value(false);
    driveTurn2(88);
    driveClamp(-900, 150, 70);
    intake.set_value(true);
    driveTurn2(-41);
    driveStraight2(975);
    intake.set_value(false);
    delay(300);
    driveStraight2(-300);
    driveTurn2(-125);
    delay(1000);
    HOOKS.move(0);
    driveStraight2(400);

  } else if(atn == 4) {
    //blue right ring
    LadyBrown.move(-127);
    driveStraight2(250);
    delay(700);
    LBMacro = 4;
    driveClamp(-1600, 150, 80);//1550
    HOOKS.move(-127);
    driveTurn2(-160);
    driveStraightC(225); //275
    driveArcRF(39, 700, 2500);
    driveStraight2(300);
    driveStraight2(-600);
    driveArcRF(35, 250, 2500);
    driveTurn2(0);
    driveStraight2(300);
    driveTurn2(34);
    intake.set_value(true);
    driveStraight2(1550, 60);
    intake.set_value(false);
    delay(300);
    driveStraight2(-300);
    driveTurn2(110);
    driveStraight2(900);




  } else if (atn == 5){
    //blue right ring rush
    LBMacro = 4;
    driveClamp(-1300, 150, 100);
    HOOKS.move(-127);
    driveTurn2(160);
    driveStraightC(225); //275
    driveArcLF(39, 700, 2500);
    driveStraight2(300);
    driveStraight2(-600);
    driveArcLF(35, 250, 2500);
    driveTurn2(0);
    driveStraight2(300);
    driveTurn2(-35);
    intake.set_value(true);
    driveStraight2(1800, 60);
    intake.set_value(false);
    delay(300);
    driveStraight2(-300);
    driveTurn2(-110);
    driveStraight2(500);
    
  } else if (atn == 6){

    //blue right ring rush
    LBMacro = 4;
    driveClamp(-1300, 150, 100);
    HOOKS.move(-127);
    driveTurn2(-160);
    driveStraightC(225); //275
    driveArcRF(39, 700, 2500);
    driveStraight2(300);
    driveStraight2(-600);
    driveArcRF(35, 250, 2500);
    driveTurn2(0);
    driveStraight2(300);
    driveTurn2(35);
    intake.set_value(true);
    driveStraight2(1800, 60);
    intake.set_value(false);
    delay(300);
    driveStraight2(-300);
    driveTurn2(110);
    driveStraight2(500);

  }
}