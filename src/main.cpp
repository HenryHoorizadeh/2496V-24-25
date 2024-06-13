// basically run all of the code here (PID, auton, etc.)

#include "main.h"
#include "api.h"
#include "auton.h"
#include "pid.h"
#include "robot.h"

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
  imu.tare_heading();

	while (true) {
    
    //printing stuff
		double chasstempC = ((RF.get_temperature() + RB.get_temperature() + LF.get_temperature() + LB.get_temperature())/4);
		
      if (time % 50 == 0 && time % 100 != 0 && time % 150 != 0){
        con.print(0, 0, "AUTON: %s           ", autstr);
      } else if (time % 50 == 0 && time % 100 != 0){
        con.print(1, 0, "Imu: %f           ", float(imu.get_heading()));
      } else if (time % 50 == 0){
        setConstants(0.075, 0, 0.1);
        con.print(2, 0, "Temp: %f        ", float(chasstempC)); 
      } 

		//chassis arcade drive
		int power = con.get_analog(ANALOG_LEFT_Y); //power is defined as forward or backward
		int RX = con.get_analog(ANALOG_RIGHT_X); //turn is defined as left (positive) or right (negative)

    //int turn = int(RX); // Normal Rates
		//int turn = int(abs(RX) * RX / 75); //X Squared Rates
    int turn = int(pow(RX, 3) / 5000); //X Cubed Rates
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
/* 
    if (((con.get_digital(E_CONTROLLER_DIGITAL_R1) && NEWR2) || (NEWR1 && con.get_digital(E_CONTROLLER_DIGITAL_R2))) || ((NEWR1 && NEWR2) || (con.get_digital(E_CONTROLLER_DIGITAL_R1) && con.get_digital(E_CONTROLLER_DIGITAL_R2)))){
      //Double Press action
    } else if  (con.get_digital(E_CONTROLLER_DIGITAL_R1)) {
			INTAKE.move(-127);
      down = false;
      R1 = true;
		}
		else if (con.get_digital(E_CONTROLLER_DIGITAL_R2)) {
			INTAKE.move(127);
      down = false;
      R1 = false;
		}
		else {
			INTAKE.move(0);
      down = false;
      R1 = false;
		}
*/

//Non Double Press Logic
    if  (con.get_digital(E_CONTROLLER_DIGITAL_R1)) {
			INTAKE.move(-127);
		}
		else if (con.get_digital(E_CONTROLLER_DIGITAL_R2)) {
			INTAKE.move(127);
		}
		else {
			INTAKE.move(0);
		}

    //pid tester
    if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_X)) {
      driveStraight2(2000);
    }

	  	time += 1;
		  pros::delay(1);
	  }
  }