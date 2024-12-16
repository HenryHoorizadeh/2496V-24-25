// basically run all of the code here (PID, auton, etc.)

#include "main.h"
#include "api.h"
#include "auton.h"
#include "pid.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "robot.h"
#include "odometry.h"
#include "pure_pursuit.h"

using namespace pros;
using namespace std;


// void resetEncoders() { //we can't add this to main.h because main.h doesn't
// refer to robot.h (where LF, LB, etc. are located) 	LF.tare_position(); //or
// set_zero_position(0) or set_zero_position(LF.get_position()); (sets current
// encoder position to 0) 	LB.tare_position(); 	RF.tare_position();
// 	RB.tare_position();
// }

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
  static bool pressed = false;
  pressed = !pressed;
  if (pressed) {
    pros::lcd::set_text(2, "I was pressed!");
  } else {
    pros::lcd::clear_line(2);
  }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  OpticalC.set_led_pwm(100);
  pros::lcd::initialize();
  pros::lcd::set_text(1, "Hello PROS User!");
  ODOMY.reset_position();
  ODOMX.reset_position();

  // pros::lcd::register_btn1_cb(on_center_button);
  // optical.set_led_pwm(100);


}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */

 

int atn = 1;
int RingColor = 2;
int pressed = 0;
string autstr;
float errorp;


 
void competition_initialize() {
    while(true) {
      // if(selec.get_value() == true) {
      //   atn ++;  
      //   delay(350);
      // }

      if(selec.get_value() == true) {
        pressed ++;  
      } else {
        pressed = 0;
      }

      if (pressed == 1){
        atn++;
      }


      //resetEncoders();
      
      if (atn == 0) {
        autstr = "NONE";
        con.print(0, 0, "Aut 0: %s", autstr);
      }
      else if (atn == 1) {
        autstr = "BLUE RIGHT";
        con.print(0, 0, "Aut 1: %s", autstr);
      }
      else if (atn == 2) {
        autstr = "BLUE LEFT";
        con.print(0, 0, "Aut 2: %s", autstr);
      }
      else if (atn == 3) {
       autstr = "RED RIGHT";
        con.print(0, 0, "Aut 3: %s", autstr);
      }
      else if (atn == 4) {
       autstr = "RED LEFT";
        con.print(0, 0, "Aut 4: %s", autstr);
      }
      else if (atn == 5) {
       autstr = "SKILLS";
        con.print(0, 0, "Aut 5: %s", autstr);
      }
      else if (atn == 6) {
       autstr = "DISRUPT";
        con.print(0, 0, "Aut 6: %s", autstr);
      } 
      else if (atn == 7) {
       atn = 0;
      }
  
      con.clear();
    }
}


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */



void opcontrol() {
  int cycle = 0;
  int time = 0;
  bool NEWL1 = false;
  bool NEWL2 = false;
  bool NEWR2 = false;
  bool NEWR1 = false;
  bool arcToggle = false;
  bool tankToggle = true;
  bool mogoToggle = true;
  bool intakeToggle = false;
  bool scrapperToggle = false;
  bool hangToggle = false;
  bool liftToggle = false;
  double maxRPM = 0;
  double motorTotal = 0;
  double avgRPM = 0;
  double liftAngle = 0; 
  double rotoAngle = 0;
  float xvelo = 0;

  imu.tare_heading();
  LIFT.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);



TEST.move(127);
//TEST2.move(127);
delay(3500);

	while (true) {

  pros::c::imu_accel_s_t accel = imu.get_accel();

  // if(abs(accel.x)>0.04){
  // xvelo += accel.x;
  // }
  xvelo += accel.x-0.032;

    OpticalC.set_led_pwm(100);

    //TEST2.move_velocity(300);
    if(TEST.get_actual_velocity() > maxRPM){
      maxRPM = TEST.get_actual_velocity();
    }

    

    motorTotal += TEST.get_actual_velocity();
    cycle++;
    avgRPM = motorTotal/cycle;



  
		//chassis arcade drive
		int power = con.get_analog(ANALOG_LEFT_Y); //power is defined as forward or backward
		int RX = con.get_analog(ANALOG_RIGHT_X); //turn is defined as left (positive) or right (negative)

    //int turn = int(RX); // Normal Rates
		//int turn = int(abs(RX) * RX / 127); //X Squared Rates
   int turn = int(pow(RX, 3) / pow(127, 2)); //X Cubed Rates
		int left = power + turn;
		int right = power - turn;

    // //switch between arcade and tank
    if (con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
      arcToggle = !arcToggle;
      tankToggle = !tankToggle;
    }


   
    if (tankToggle) {
      LF.move(con.get_analog(ANALOG_LEFT_Y));
      LM.move(con.get_analog(ANALOG_LEFT_Y));
      LB.move(con.get_analog(ANALOG_LEFT_Y));
      RF.move(con.get_analog(ANALOG_RIGHT_Y));
      RM.move(con.get_analog(ANALOG_RIGHT_Y));
      RB.move(con.get_analog(ANALOG_RIGHT_Y));
    }
    if (arcToggle) {
      LF.move(left);
      LM.move(left);
      LB.move(left);
      RF.move(right);
      RM.move(right);
      RB.move(right);
    }



    //auton selector
    if (selec.get_value() == true) { 
      atn++;
      delay(350);
    }
      // brain was here
    // switch(atn){
    //   case 0:
    //     autstr = "Auton 0";
    //     break;
    //   case 1:
    //     autstr = "Auton 1";
    //     break;
    //   case 2:
    //     autstr = "Auton 2";
    //     break;
    //   case 3:
    //     autstr = "Auton 3";
    //     break;
    //   case 4:
    //     autstr = "Auton 4";
    //     break;
    //   case 5:
    //     autstr = "Auton 5";
    //     break;
    //   case 6:
    //     autstr = "Auton 6";
    //     break;
    //   case 7:
    //     atn = 0;
    //     break;

    // }
    
    if (atn == 0) {
      autstr = "NONE";
    }
    if (atn == 1) {
      autstr = "BLUE RIGHT";
    }
    else if (atn == 2) {
      autstr = "BLUE LEFT";
    }
    else if (atn == 3) {
      autstr = "RED RIGHT";
    }
    else if (atn == 4) {
      autstr = "RED LEFT";
    }
    else if (atn == 5) {
      autstr = "SKILLS";
    } 
    else if (atn == 6) {
      autstr = "Auton 6";
    }
    else if (atn == 7) {
      atn = 0;
    }

  if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)){
    NEWR1 = true;
  } else {
    NEWR1 = false;
  }

  if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_R2)){
    NEWR2 = true;
  } else {
    NEWR2 = false;
  }

  if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)){
    NEWL2 = true;
  } else {
    NEWL2 = false;
  }

  
  if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)){
    NEWL1 = true;
  } else {
    NEWL1 = false;
  }

//Double Press Logic

    if (((con.get_digital(E_CONTROLLER_DIGITAL_R1) && NEWR2) || (NEWR1 && con.get_digital(E_CONTROLLER_DIGITAL_R2))) || ((NEWR1 && NEWR2) || (con.get_digital(E_CONTROLLER_DIGITAL_R1) && con.get_digital(E_CONTROLLER_DIGITAL_R2)))){
      //Double Press action
      INTAKE.move(127);
      HOOKS.move(-95);
    // HOOKS.move(-127);
    } else if  (con.get_digital(E_CONTROLLER_DIGITAL_R1)) {
			INTAKE.move(-127);
      HOOKS.move(-127);
		} else if (con.get_digital(E_CONTROLLER_DIGITAL_R2)) {
			INTAKE.move(127);
     HOOKS.move(127);
		} else {
			INTAKE.move(0);
      HOOKS.move(0);
		}
    // sreverse = false;
    // stallProtection = true;
    // stall();
    // hooks(127);


// INTAKE.move(127);
// ColorSort(1);
//lift
    if (con.get_digital(E_CONTROLLER_DIGITAL_L1)) {
      LIFT.move(127);
      liftAngle = LIFT.get_position();
      liftToggle = false;
    }
    else if (con.get_digital(E_CONTROLLER_DIGITAL_L2)){
      LIFT.move(-127);
      liftAngle = LIFT.get_position();
      liftToggle = false;
    } else if (liftToggle){
      setConstants(LIFT_KP2,LIFT_KI2,LIFT_KD2);
      if(roto.get_angle() < 15000){
        rotoAngle = roto.get_angle() + 36000;
      } else {
        rotoAngle = roto.get_angle();
      }
      LIFT.move(calcPID(30200,(rotoAngle),0,0,true));
    } else {
      setConstants(LIFT_KP,LIFT_KI,LIFT_KD);
      LIFT.move(calcPID(liftAngle,LIFT.get_position(),0,0,true));
    }

//Non Double Press Logic
    if (con.get_digital(E_CONTROLLER_DIGITAL_R1)) {
			INTAKE.move(127);
		} 
    else if (con.get_digital(E_CONTROLLER_DIGITAL_R2)) {
			INTAKE.move(-127);
		} 
    else {
			INTAKE.move(0);
		}
    




    //pid tester
    if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_X)) {
      // longValues = true;
      // driveClampS(-2500, 400, 70);
      // longValues = false;
    //   chasMove(40,40,40,40,40,40);
    //  hang.set_value(true);
    //   delay(2000);

      
      //driveArcLF(130, 600, 3000);
      // mogoValues=true;
      //  driveTurn2(40);
      // setPosition(0,0,0);
      // boomerang(0, -1000);
      //boomerang(-1000, 1000);
     // boomerang(0, 0);
     //setPosition(0, 0, 0);
     //boomerang(-1000, 1000);
     // driveArcLF(-90, 100, 1800);

    //  driveArcL(90, 300, 3000);


  // setPosition(0, 0, 0);
  // //boomerang(0, 90);
  // boomerang(48, 60);
  // boomerang(0, 10);


  
    //  boomerang(-3500, 3500);
    //  boomerang(-3500, 0);
    //  boomerang(0, 0);
    
    // driveTurn2(175);
    // driveStraight(625);
    // LIFT.move(-127);
    // driveStraight2(-1000);
    // driveTurn2(100);
    // driveStraight2(1000);
    // mogoValues = true;
    // driveTurn(175);

    // driveArcLF(90,300,1800);
    driveStraightC(350);
    driveArcLF(45, 50, 2000);
    driveStraightC(1000);
    driveArcRF(45, 300, 1800);
    driveStraight2(200);
   // driveStraight2(100);
    
    // initializePath();
    // initializePathDistances();
    // purePursuitController();


     
      // while(true){
      // odometry2();
      // delay(5);
      // }
    }

    odometry2();

    if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)){
        intakeToggle = !intakeToggle;
    }

    if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT)){
        liftToggle = !liftToggle;
    }

  intake.set_value(intakeToggle);
      if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_A)){
        hangToggle = !hangToggle;
    }

  hang.set_value(hangToggle);


    if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)){
        mogoToggle = !mogoToggle;
    }

  mogo.set_value(mogoToggle);

      if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
        scrapperToggle = !scrapperToggle;
    }

  scrapper.set_value(scrapperToggle);
  //piston2.set_value(wingToggle);



  // if (con.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
  //    piston.set_value(true);
  // } else {
  //    piston.set_value(false);
  // }

      //printing stuff
		double chasstempC = ((RF.get_temperature() + RB.get_temperature() + LF.get_temperature() + LB.get_temperature())/4);
    if (time % 50 == 0 && time % 100 != 0 && time % 150 != 0){
      con.print(0, 0, "AUTON: %s           ", autstr);
      //con.print(0, 0, "imu: %f         ", imu.get_heading());
    } else if (time % 100 == 0 && time % 150 != 0){
      //con.print(1, 0, "error: %f           ",float(chasstempC));
      con.print(1, 0, "MAX: %f           ",float(maxRPM));
    } else if (time % 150 == 0){
      con.print(2, 0, "AVG: %f        ", float(avgRPM)); 
      // pros::lcd::print(1, "errorp:%f ", float(error));
    } 

	  	time += 1;
		  delay(1);
	  }
  }