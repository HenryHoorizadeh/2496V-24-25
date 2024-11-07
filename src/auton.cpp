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
    HOOKS.move(-127);
    LIFT.move_relative(-1000, 125);
    delay(400);
    driveStraight2(250);
    LIFT.move(127);
    delay(1200);
    driveClampS(-1350, 400,90);
    LIFT.move(20);
    driveTurn2(-110);
    INTAKE.move(127);
    HOOKS.move(127);
    driveStraight2(500);
    driveTurn2(115);
    driveStraight2(550);
    driveTurn2(-140);
    driveStraight2(300);
    driveTurn2(-130);
    driveStraight2(300);
    driveTurn2(-170);
    driveStraight2(-600);
    // LIFT.move_relative(-1150, 125);
    driveTurn2(-90);









    // RingColor = 2;
    // INTAKE.move(-127);
    // HOOKS.move(-127);
    // LIFT.move_relative(-1000, 125);
    // delay(500);
    // driveStraight2(250);
    // LIFT.move(127);
    // delay(900);
    // driveClampS(-1400, 400, 50);//-1400
    // LIFT.move(0);




    // driveTurn2(18);
    // intake.set_value(true);
    // INTAKE.move(127);
    // driveClampS(1000, -100, 50); //900
    // HOOKS.move(127);
    // delay(200);
    // intake.set_value(false);
    // driveStraight2(-200);
    // // delay(200);
    // driveStraight2(-800);
    // driveTurn2(-115);
    // driveStraight2(450);
    // driveTurn2(160); //150
    // driveStraight2(400);
    // driveTurn2(145);
    // driveStraight2(-500);
    // driveTurn2(160);//175
    // driveStraight2(625);
    // LIFT.move(-127);
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
//setPosition(0,0, -147);
    INTAKE.move(-127);
    HOOKS.move(-127);
    LIFT.move_relative(-1000, 125);
    delay(500);
    driveStraight2(250);
    LIFT.move(127);
    delay(900);
    driveClampS(-1500, 400, 100);//-1400



    driveTurn2(-18);
    intake.set_value(true);
    INTAKE.move(127);
    driveStraightSlow(830, 35); //900 //50% //930
    HOOKS.move(127);
    delay(200);
    intake.set_value(false);
    driveStraightSlow(-550, 75);
    driveStraight2(300);

    driveTurn2(-60);
    LIFT.move(10);
    //delay(500);
    mogo.set_value(false);

    driveTurn2(131);//137
    HOOKS.move(0);
    driveStraight2(1400);
    driveTurn2(21);
    driveClampS(-410, 20, 40); //make further
    INTAKE.move(127);
    HOOKS.move(127);




       //awp red left
    // RingColor = 2;
    // INTAKE.move(-127);
    // HOOKS.move(-127);
    // LIFT.move_relative(-1000, 125);
    // delay(400);
    // driveStraight2(250);
    // LIFT.move(127);
    // delay(1200);
    // driveClampS(-1200, 100,40);
    // LIFT.move(20);
    // driveTurn2(-112);
    // INTAKE.move(127);
    // HOOKS.move(127);
    // driveStraight2(500);
    // driveTurn2(115);
    // driveStraight2(525);//550
    // driveTurn2(-140);
    // driveStraight2(300);
    // delay(500);
    // driveTurn2(-130);
    // driveStraight2(300);
    // delay(500);
    // driveStraight2(-500);
    // driveTurn2(-170);
    // driveStraight2(-600);
    // // LIFT.move_relative(-1150, 125);
    // driveTurn2(110);
    // // driveStraight2(600);


    // RingColor = 2;
    // //setPosition(0,0, -147);
    // INTAKE.move(-127);
    // HOOKS.move(-127);
    // LIFT.move_relative(-1000, 125);
    // delay(500);
    // driveStraight2(250);
    // LIFT.move(127);
    // delay(900);
    //  LIFT.move(127);
    // driveClampS(-1400, 400, 50);//-1400
    


    // driveTurn2(-18);
    // intake.set_value(true);
    // INTAKE.move(127);
    // driveStraightSlow(950, 40); //900 //50% //930
    // HOOKS.move(127);
    // delay(200);
    // intake.set_value(false);
    // driveStraightSlow(-550, 75);
    // driveStraight2(300);

    // driveStraight2(-700);
    // driveTurn2(110);
    // driveStraight2(800);


    // driveTurn2(-75);
    // LIFT.move_relative(-1400, 125);
    // delay(700);
    // driveStraight2(1200);
    

    // driveTurn2(-60);
    // LIFT.move(10);
    // //delay(500);
    // mogo.set_value(false);

    // driveTurn2(131);//137
    // HOOKS.move(0);
    // driveStraight2(1400);
    // driveTurn2(21);
    // driveClampS(-410, 20, 40); //make further
    // INTAKE.move(127);
    // HOOKS.move(127);



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
      // driveStraight2(700);
      // INTAKE.move(300);
      // driveTurn2(20);
      // driveStraight2(700);
      // INTAKE.move(0);
      // scrapper.set_value(true);
      // driveStraight2(-500);
      // scrapper.set_value(false);
      // driveTurn2(-70);
      // driveStraight(-400);
      // mogo.set_value(true);
      // delay(500);
      // driveTurn2(-30);
      // driveStraight2(500);
      

      // INTAKE.move(300);
      // driveStraight2(1000);
      // INTAKE.move(300);
      // mogo.set_value(false);
      // driveTurn2(75);
      // driveStraight2(-1000);
      // mogo.set_value(true);
      // driveTurn2(-50);
      // driveStraight2(1100);
      // INTAKE.move(-200);
      // driveStraight2(100);
      // INTAKE.move(300);
    //red right
    } else if (atn == 3) { 
      //not mirrored
    RingColor = 2;
    //setPosition(0,0, -147);
    INTAKE.move(-127);
    HOOKS.move(-127);
    LIFT.move_relative(-1000, 125);
    delay(500);
    driveStraight2(250);
    LIFT.move(127);
    delay(900);
    driveClampS(-1500, 400, 50);//-1400
    LIFT.move(10);
    driveTurn2(17);
    intake.set_value(true);
    INTAKE.move(127);
    delay(200);
    driveStraightSlow(930, 30); //900 //50%
    driveStraight2(-550);
    HOOKS.move(0);
    LIFT.move(-127);
    delay(500);
    driveStraight2(300);





    // intake.set_value(false);
    // driveStraight2(200);
    // HOOKS.move(127);
    // delay(200);
    // driveStraight2(-350);
    // driveTurn2(-55);
    // mogo.set_value(false);
    // driveTurn2(-140);
    // HOOKS.move(0);
    // driveStraight2(1400);
    // driveTurn2(-56);
    // driveClampS(-340, 90, 25);
    // INTAKE.move(127);
    // HOOKS.move(127);

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
    HOOKS.move(-127);
    LIFT.move_relative(-1000, 125);
    delay(400);
    driveStraight2(250);
    LIFT.move(127);
    delay(1200);
    driveClampS(-1200, 100,40);
    LIFT.move(20);
    driveTurn2(112);
    INTAKE.move(127);
    HOOKS.move(127);
    driveStraight2(500);
    driveTurn2(-115);
    driveStraight2(525);//550
    driveTurn2(140);
    driveStraight2(300);
    delay(500);
    driveTurn2(130);
    driveStraight2(300);
    delay(500);
    driveStraight2(-500);
    driveTurn2(170);
    driveStraight2(-600);
    // LIFT.move_relative(-1150, 125);
    driveTurn2(-110);
    // driveStraight2(600);



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
/// skills 
LIFT.move_relative(-900, 125);
delay(200);
HOOKS.move(-127);
delay(600);
LIFT.move(127);
delay(300);
driveStraight2(-275);
driveTurn2(-90);
driveClampS(-825, 100, 55); //-875
//driveStraight2(200);
HOOKS.move(127);
INTAKE.move(127);
mogoValues = true;
driveTurn2(180);
driveStraightC(200);
driveArcLF(70, 500, 1800);
driveStraight2(500);
driveTurn2(-20); //-15
driveArcRF(23,350,1800);
driveStraightSlow(2100,40);
delay(1000);
driveTurn2(125);
driveStraight2(400);
driveTurn2(-155);
driveStraight2(-300);
mogo.set_value(false);
HOOKS.move(-127);
mogoValues = false;
delay(200);
driveStraight2(250); //300
driveTurn2(90);
longValues = true;
driveStraight2(-1750);
longValues = false;
driveClampS(-1100, 200, 60);
driveStraight2(200);
HOOKS.move(127);

driveTurn2(180);
driveArcRF(90, 700, 1800);
driveStraight2(500);
driveTurn2(20); //-15
driveArcLF(23,280,1800);
driveStraightSlow(2100,40);

delay(1000);
driveTurn2(-125);
driveStraight2(400);
driveTurn2(155);
driveStraight2(-300);
mogo.set_value(false);
HOOKS.move(-127);
mogoValues = false;

driveStraight2(300);
driveTurn2(127);
HOOKS.move(0);
driveStraight2(2500);

INTAKE.move(127);
driveTurn2(-135);
HOOKS.move_relative(500, 600);
chasMove(40,40,40,40,40,40);
hang.set_value(true);
delay(2000);
hang.set_value(false);
driveStraight2(-400);
driveStraight2(1000);
driveTurn2(-45);
driveClampS(-1200,100,40);
mogoValues = true;
HOOKS.move(127);
driveTurn2(-62);
driveStraight2(1900);
driveTurn2(180);
driveStraightSlow(1050, 40);
delay(1000);
driveTurn2(-55);
driveStraight2(400);
driveTurn2(-163); //155
HOOKS.move(0);
scrapper.set_value(true);
driveStraight2(100);
driveTurn2(45); 
scrapper.set_value(false);
driveStraight2(-300);
mogo.set_value(false);
HOOKS.move(-127);
mogoValues = false;
driveStraight2(500);
driveTurn2(100);
driveStraight2(5000);
INTAKE.move(-127);
driveStraight2(-700);
driveTurn2(-45);
hang.set_value(true);
driveStraight2(1500);
LIFT.move(127);





//old skills 
/*
LIFT.move_relative(-900, 125);
delay(200);
HOOKS.move(-127);
delay(600);
LIFT.move(127);
delay(300);
driveStraight2(-275);
driveTurn2(-90);
driveClampS(-825, 100, 55); //-875
//driveStraight2(200);
HOOKS.move(127);
INTAKE.move(127);
mogoValues = true;
driveTurn2(180);
driveStraight2(750);
driveTurn2(125);
driveStraight2(1100); //1250
driveTurn2(-20); //-15
driveStraight2(650);//800
driveTurn2(0);
driveStraightSlow(1050, 35);//40
delay(1000);
driveTurn2(125);
driveStraight2(400);
driveTurn2(-155);
driveStraight2(-300);
mogo.set_value(false);
HOOKS.move(-127);
mogoValues = false;
delay(200);
driveStraight2(300);
driveTurn2(89);
longValues = true;
driveStraight2(-1750);
longValues = false;
driveClampS(-1100, 200, 60);
driveStraight2(200);




HOOKS.move(127);
HOOKS.move(127);
INTAKE.move(127);
mogoValues = true;
driveTurn2(180);
driveStraight2(750);
driveTurn2(-125);
driveStraight2(1250); //1300
driveTurn2(20); //-15
driveStraight2(800);
driveTurn2(0);
driveStraightSlow(1050, 40);
delay(1000);
driveTurn2(-125);
driveStraight2(400);
driveTurn2(158); //155
driveStraight2(-300);
mogo.set_value(false);
HOOKS.move(-127);
mogoValues = false;
delay(200);
driveStraight2(300);
driveTurn2(127);
HOOKS.move(0);
driveStraight2(2500);

INTAKE.move(127);
driveTurn2(-135);
HOOKS.move_relative(500, 600);
chasMove(40,40,40,40,40,40);
hang.set_value(true);
delay(2000);
hang.set_value(false);
driveStraight2(-400);
driveStraight2(1000);
driveTurn2(-45);
driveClampS(-1200,100,40);
mogoValues = true;
HOOKS.move(127);
driveTurn2(-62);
driveStraight2(1900);
driveTurn2(180);
driveStraightSlow(1050, 40);
delay(1000);
driveTurn2(-55);
driveStraight2(400);
driveTurn2(-163); //155
HOOKS.move(0);
scrapper.set_value(true);
driveStraight2(100);
driveTurn2(45); 
scrapper.set_value(false);
driveStraight2(-300);
mogo.set_value(false);
HOOKS.move(-127);
mogoValues = false;
driveStraight2(500);
driveTurn2(100);
driveStraight2(5000);
INTAKE.move(-127);
driveStraight2(-700);
driveTurn2(-45);
hang.set_value(true);
driveStraight2(1500);
LIFT.move(127);


*/











// driveStraight2(600);
// driveTurn2(16);
// driveClampS(-3000, 100, 60);
// HOOKS.move(0);
// INTAKE.move(0);
// driveTurn2(150);
// scrapper.set_value(true);
// driveStraight2(800);
// driveTurn2(-45);
// LIFT.move_relative(-400, 125);











//rush red right
// driveStraight2(1100);
// scrapper.set_value(true);
// driveStraight2(-1000);

  
  } else if (atn == 6){
    //50 skills starts here
    // https://www.youtube.com/watch?v=5inrqB0fCFc
    //scoring alliance wall stake
    driveStraight2(100);
    LIFT.move(127);
    driveStraight2(-400);
    //collecting rings
    driveTurn2(-90);
    driveClampS(-350,50, 50);
    driveTurn2(90);
    INTAKE.move(127);
    HOOKS.move(127);
    driveStraight2(100);
    driveTurn2(15);
    driveStraight2(200);
    driveArcLF(30,200,4);
    driveTurn2(130);
    //scoring wall stake
    HOOKS.move(-127);
    driveTurn2(-90);
    LIFT.move(127);
    driveStraight2(100);
    while (LIFT.move(-127)){
      driveStraight2(-200);
    }
    driveTurn2(90);
    HOOKS.move(127);
    driveStraight2(500);
    driveTurn2(-140);
    driveArcLF(30,2,4);
    mogo.set_value(false);
    driveStraight2(50);
    driveTurn2(210);
    //second mobile stake;
    driveClampS(1000,25,100);
    driveTurn2(-90);
    driveStraight2(200);
    driveTurn2(45);
    driveStraight2(200);
    driveStraight2(-200);
    driveTurn2(-140);
    driveStraight2(100);
    driveTurn2(90);
    driveStraight2(200);
    driveTurn2(65);
    driveStraight2(50);
    driveTurn(50);
    driveStraight2(-30);
    mogo.set_value(false);
    //scoring another wall stakes
    driveTurn2(-10);
    HOOKS.move(-127);
    driveStraight2(300);
    driveTurn(90);
    HOOKS.move(127);
    driveStraight2(50);
        while (LIFT.move(-127)){
      driveStraight2(-200);
    }
    //getting another mobile stake
    driveTurn(140);
    driveStraight2(200);
    driveTurn(180);
    driveStraight2(-50); 
    driveArcLF(30,100,4);
    mogo.set_value(true);
    
    //possibly correct spot here using boomerang or odom?

    //  RingColor = 2;
    // //setPosition(0,0, -147);
    // INTAKE.move(-127);
    // LIFT.move_relative(-1000, 125);
    // delay(500);
    // driveStraight2(250);
    // LIFT.move(127);
    // delay(900);
    // driveClampS(-1400, 400, 50);//-1400
    // LIFT.move(0);


    // driveTurn2(18);
    // intake.set_value(true);
    // INTAKE.move(127);
    // driveStraightSlow(1000, 70); //900 //50%
    // HOOKS.move(127);
    // delay(200);
    // intake.set_value(false);
    // driveStraight2(-200);
    // // delay(200);
    // driveStraight2(-800);
    // driveTurn2(-115); //-115
    // driveStraight2(450);
    // driveTurn2(155); //160 //150
    // driveStraight2(400);
    // driveTurn2(145);
    // driveStraight2(-500);
    // driveTurn2(175);//175
    // driveStraight2(625);
    // LIFT.move(-127);
    // driveTurn2(55);
    // driveStraight2(1000);
    //  driveArcLF(-90, 150, 1800);
    //  driveStraight2(-1000);
    //  boomerang(300, -1000);
    // driveStraight2(-1000);
    // delay(200);
    // driveTurn2(-110);
    // driveStraight2(1000);
  }
}