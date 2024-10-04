// basically run all of the code here (PID, auton, etc.)

#include "main.h"
#include "api.h"
#include "auton.h"
#include "pid.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "robot.h"
#include "odometry.h"

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


 
void competition_initialize() {
    while(true) {
      if(selec.get_value() == true) {
        atn ++;  
        delay(350);
      }
      //resetEncoders();
      
      if (atn == 0) {
        autstr = "Skills";
        con.print(0, 0, "Aut 0: %s", autstr);
      }
      else if (atn == 1) {
        autstr = "NONE";
        con.print(0, 0, "Aut 1: %s", autstr);
      }
      else if (atn == 2) {
        autstr = "AWPON";
        con.print(0, 0, "Aut 2: %s", autstr);
      }
      else if (atn == 3) {
       autstr = "AWPOFF";
        con.print(0, 0, "Aut 3: %s", autstr);
      }
      else if (atn == 4) {
       autstr = "ML1";
        con.print(0, 0, "Aut 4: %s", autstr);
      }
      else if (atn == 5) {
       autstr = "DEFN1";
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
  bool arcToggle = true;
  bool tankToggle = false;
  bool mogoToggle = false;
  bool intakeToggle = false;
  bool scrapperToggle = false;
  bool hangToggle = false;
  double maxRPM = 0;
  double motorTotal = 0;
  double avgRPM = 0;
  double liftAngle = 0; 

  imu.tare_heading();
  LIFT.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

//TEST.move(127);
//TEST2.move(127);
//delay(1000);

	while (true) {
    OpticalC.set_led_pwm(100);

    //TEST2.move_velocity(300);
    if(RF.get_actual_velocity() > maxRPM){
      maxRPM = RF.get_actual_velocity();
    }

    

    motorTotal += TEST.get_actual_velocity();
    cycle++;
    avgRPM = motorTotal/cycle;



    
    //printing stuff
		double chasstempC = ((RF.get_temperature() + RB.get_temperature() + LF.get_temperature() + LB.get_temperature())/4);
		
    if (time % 50 == 0 && time % 100 != 0 && time % 150 != 0){
      con.print(0, 0, "AUTON: %s           ", autstr);
    } else if (time % 100 == 0 && time % 150 != 0){
      con.print(1, 0, "Color: %f           ", float(OpticalC.get_hue()));
    } else if (time % 150 == 0){
      con.print(2, 0, "Count: %f        ", float(ColorCount)); 
    } 
    

		//chassis arcade drive
		int power = con.get_analog(ANALOG_LEFT_Y); //power is defined as forward or backward
		int RX = con.get_analog(ANALOG_RIGHT_X); //turn is defined as left (positive) or right (negative)

     int turn = int(RX); // Normal Rates
		//int turn = int(abs(RX) * RX / 127); //X Squared Rates
    //int turn = int(pow(RX, 3) / 15000); //X Cubed Rates
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
    if (selec.get_value() == true) { // brain was here
      atn++;
      delay(350);
    }
    
    if (atn == 0) {
      autstr = "Auton 0";
    }
    if (atn == 1) {
      autstr = "Auton 1";
    }
    else if (atn == 2) {
      autstr = "Auton 2";
    }
    else if (atn == 3) {
      autstr = "Auton 3";
    }
    else if (atn == 4) {
      autstr = "Auton 4";
    }
    else if (atn == 5) {
      autstr = "Auton 5";
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
      HOOKS.move(-110);
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

// INTAKE.move(127);
// ColorSort(1);
//lift
    if (con.get_digital(E_CONTROLLER_DIGITAL_L1)) {
      LIFT.move(127);
      liftAngle = LIFT.get_position();
    }
    else if (con.get_digital(E_CONTROLLER_DIGITAL_L2)){
      LIFT.move(-127);
      liftAngle = LIFT.get_position();
    }
    else {
      setConstants(LIFT_KP,LIFT_KI,LIFT_KD);
      LIFT.move(calcPID(liftAngle,LIFT.get_position(),0,0,true));
    }

//Non Double Press Logic
    // if (con.get_digital(E_CONTROLLER_DIGITAL_R1)) {
		// 	INTAKE.move(127);
		// } 
    // else if (con.get_digital(E_CONTROLLER_DIGITAL_R2)) {
		// 	INTAKE.move(-127);
		// } 
    // else {
		// 	INTAKE.move(0);
		// }




    //pid tester
    if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_X)) {
      driveArcLF(130, 600, 3000);
      //driveTurn(5);
      // setPosition(0,0,0);
      // boomerang(0, -1000);
      //boomerang(-1000, 1000);
     // boomerang(0, 0);
      // while(true){
      // odometry();
      // delay(1);
      // }
    }

    if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)){
        intakeToggle = !intakeToggle;
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

	  	time += 1;
		  delay(1);
	  }
  }