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

 

int atn = 8;
int RingColor = 2;
int color = 0;
int pressed = 0;
string autstr;
float errorp;
bool mogoToggle = false;


 
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

      if(con.get_digital_new_press(E_CONTROLLER_DIGITAL_A)){
        atn++;
      }
      if(atn>8){
        atn = 0;
      }

 


      //resetEncoders();
      
      if (atn == 0) {
        autstr = "NONE";
        con.print(0, 0, "Aut 0: %s", autstr);
      }
      else if (atn == 1) {
        autstr = " RED LEFT RING";
        con.print(0, 0, "Aut 1: %s", autstr);
      }
      else if (atn == 2) {
        autstr = "RED RIGHT GOAL";
        con.print(0, 0, "Aut 2: %s", autstr);
      }
      else if (atn == 3) {
       autstr = "BLUE LEFT MOGO";
        con.print(0, 0, "Aut 3: %s", autstr);
      }
      else if (atn == 4) {
       autstr = "BLUE RIGHT RING";
        con.print(0, 0, "Aut 4: %s", autstr);
      }
      else if (atn == 5) {
       autstr = "BLUE RIGHT RING RUSH";
        con.print(0, 0, "Aut 5: %s", autstr);
      }
      else if (atn == 6) {
       autstr = "RED RIGHT RING RUSH";
        con.print(0, 0, "Aut 6: %s", autstr);
      } 
      else if (atn == 7) {
        autstr = "BLUE GOAL SAFE";
         con.print(0, 0, "Aut 6: %s", autstr);
       } 
       else if (atn == 8) {
        autstr = "RED GOAL SAFE";
         con.print(0, 0, "Aut 6: %s", autstr);
       } 
      else if (atn == 9) {
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
  bool intakeToggle = false;
  bool doinkerToggle = false;
  bool doinkerClampToggle = false;
  bool liftToggle = false;
  double maxRPM = 0;
  double motorTotal = 0;
  double avgRPM = 0;
  double liftAngle = 0; 
  double rotoAngle = 0;
  float xvelo = 0;
  int macro = 1;
  bool macroControl = false;
  bool hookControl = false;






  imu.tare_heading();
  LadyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);



// while (true){
//   LF.move(con.get_analog(ANALOG_LEFT_Y));
//   LM.move(con.get_analog(ANALOG_LEFT_Y));
//   LB.move(con.get_analog(ANALOG_LEFT_Y));
//   RF.move(con.get_analog(ANALOG_RIGHT_Y));
//   RM.move(con.get_analog(ANALOG_RIGHT_Y));
//   RB.move(con.get_analog(ANALOG_RIGHT_Y));
// }
  


TEST.move(127);
//TEST2.move(127);
//delay(3500);



	while (true) {

    // color = 1;
    // ColorSort();
    //ColorSorter.set_value(true);
//MACROO!!!!!!!!!!!!!!!!!!!!!
    liftAngle = 36000-roto.get_angle();
    
    if(liftAngle > 30000){
      liftAngle -= 36000;
    }
    if(con.get_digital(E_CONTROLLER_DIGITAL_L1)){
      // if(liftAngle < 15500){
      // LadyBrown.move(-127);
      // macroControl = false;
      // } else {
      //   macroControl = true;
      //   macro = 1;
      // }

        LadyBrown.move(127);
        macroControl = false;

    } else if(con.get_digital(E_CONTROLLER_DIGITAL_L2)){
      LadyBrown.move(-127);
      macroControl = false;
    } else if (macroControl == false){
      LadyBrown.move(0);
    }

    if(con.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
      macro ++;
      macroControl = true;
      //hookControl = true;
      if(macro == 2 || macro == 3){
        hookControl = true;
      }
    }

    // if(con.get_digital(E_CONTROLLER_DIGITAL_Y)){
    //   macroControl = true;
    //   macro = 0;
    // }
    if(con.get_digital(E_CONTROLLER_DIGITAL_Y)){
      macroControl = true;
      hookControl = true;
      macro = 1;
    }

    if (con.get_digital(E_CONTROLLER_DIGITAL_R1)) {
			HOOKS.move(127);
      HOOKS.tare_position();
      hookControl = false;
		} 
    else if (con.get_digital(E_CONTROLLER_DIGITAL_R2)) {
	    HOOKS.move(-127);
      HOOKS.tare_position();
      hookControl = false;
		} 
    else if(hookControl == false) {
			HOOKS.move(0);
      HOOKS.tare_position();
		}

    if(macroControl){
      
      if(macro == 0){
        setConstants2(0.7, 0, 0);
        LadyBrown.move(-calcPIDlift(16000, liftAngle, 0, 0, 1.0));
      } else if(macro == 1){
        setConstants2(0.05, 0, 0);
        LadyBrown.move(-calcPIDlift(16000, liftAngle, 0, 0, 1.0));
      } else if(macro == 2){
        setConstants2(0.03, 0, 500);
        LadyBrown.move(-calcPIDlift(2700, liftAngle, 0, 0, 1.0));// clamp(-calcPIDlift(2000, liftAngle, 0, 0, 1.0), -80.0, 80.0)
      } else if(macro == 3){
        setConstants2(0.05, 0, 500);
        LadyBrown.move(-calcPIDlift(5200, liftAngle, 0, 0, 1.0));
      } else {
        macro = 2;
      }
    }


    if(hookControl){
      setConstants(1, 0, 0);
      HOOKS.move(calcPID2(120, HOOKS.get_position(), 0, 0, true));
      if(abs(120 - HOOKS.get_position()) < 10){
        hookControl = false;
      }
    } 

    





  




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
    if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT)) {
      arcToggle = !arcToggle;
      tankToggle = !tankToggle;
    }


   
    if (tankToggle) {
      // LF.move(int(abs(con.get_analog(ANALOG_LEFT_Y)) * con.get_analog(ANALOG_LEFT_Y) / 127));
      // LM.move(int(abs(con.get_analog(ANALOG_LEFT_Y)) * con.get_analog(ANALOG_LEFT_Y) / 127));
      // LB.move(int(abs(con.get_analog(ANALOG_LEFT_Y)) * con.get_analog(ANALOG_LEFT_Y) / 127));
      // RF.move(int(abs(con.get_analog(ANALOG_RIGHT_Y)) * con.get_analog(ANALOG_RIGHT_Y) / 127));
      // RM.move(int(abs(con.get_analog(ANALOG_RIGHT_Y)) * con.get_analog(ANALOG_RIGHT_Y) / 127));
      // RB.move(int(abs(con.get_analog(ANALOG_RIGHT_Y)) * con.get_analog(ANALOG_RIGHT_Y) / 127));
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
      autstr = "SKILLS";
    }
    if (atn == 1) {
      autstr = "RED LEFT RING";
    }
    else if (atn == 2) {
      autstr = "RED RIGHT GOAL";
    }
    else if (atn == 3) {
      autstr = "BLUE LEFT MOGO";
    }
    else if (atn == 4) {
      autstr = "BLUE RIGHT RING";
    }
    else if (atn == 5) {
      autstr = "BLUE RIGHT RING RUSH";
    } 
    else if (atn == 6) {
      autstr = "RED RIGHT RING RUSH";
    }
    else if (atn == 7) {
      autstr = "BLUE GOAL SAFE";
    }
    else if (atn == 8) {
      autstr = "RED GOAL SAFE";
    }
    else if (atn == 9) {
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

  // if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)){
  //   NEWL2 = true;
  // } else {
  //   NEWL2 = false;
  // }

  
  // if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)){
  //   NEWL1 = true;
  // } else {
  //   NEWL1 = false;
  // }

//Double Press Logic

    // if (((con.get_digital(E_CONTROLLER_DIGITAL_R1) && NEWR2) || (NEWR1 && con.get_digital(E_CONTROLLER_DIGITAL_R2))) || ((NEWR1 && NEWR2) || (con.get_digital(E_CONTROLLER_DIGITAL_R1) && con.get_digital(E_CONTROLLER_DIGITAL_R2)))){
    //   //Double Press action
    //   INTAKE.move(127);
    //   HOOKS.move(-95);
    // // HOOKS.move(-127);
    // } else if  (con.get_digital(E_CONTROLLER_DIGITAL_R1)) {
		// 	INTAKE.move(-127);
    //   HOOKS.move(-127);
		// } else if (con.get_digital(E_CONTROLLER_DIGITAL_R2)) {
		// 	INTAKE.move(127);
    //  HOOKS.move(127);
		// } else {
		// 	INTAKE.move(0);
    //   HOOKS.move(0);
		// }
    // sreverse = false;
    // stallProtection = true;
    // stall();
    // hooks(127);


// INTAKE.move(127);
// ColorSort(1);
//lift
    // if (con.get_digital(E_CONTROLLER_DIGITAL_L1)) {
    //   LBD.move(127);
    //   liftAngle = LIFT.get_position();
    //   liftToggle = false;
    // }
    // else if (con.get_digital(E_CONTROLLER_DIGITAL_L2)){
    //   LBD.move(-127);
    //   liftAngle = LIFT.get_position();
    //   liftToggle = false;
    // } else if (liftToggle){
    //   setConstants(LIFT_KP2,LIFT_KI2,LIFT_KD2);
    //   if(roto.get_angle() < 15000){
    //     rotoAngle = roto.get_angle() + 36000;
    //   } else {
    //     rotoAngle = roto.get_angle();
    //   }
    //   LBD.move(calcPID(30200,(rotoAngle),0,0,true));
    // } else {
    //   setConstants(LIFT_KP,LIFT_KI,LIFT_KD);
    //   LBD.move(calcPID(liftAngle,LIFT.get_position(),0,0,true));
    // }




    // if (con.get_digital(E_CONTROLLER_DIGITAL_L1)) {
		// 	LadyBrown.move(127);
		// } 
    // else if (con.get_digital(E_CONTROLLER_DIGITAL_L2)) {
		// 	LadyBrown.move(-127);
		// } 
    // else {
		// 	LadyBrown.move(0);
		// }



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






//hello
    //pid tester
    if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)) {
      driveTurn2(-135);
      driveArcRF(35, 3300, 2000);

    }
      //driveStraightR(2000);
      // driveStraight2(1000);
      // driveTurn2(180);
      // driveTurn2(-60);
      // longValues = true;
      
      // driveClampS(-2500, 400, 70);
      // longValues = false;
    //   chasMove(40,40,40,40,40,40);
    //  hang.set_value(true);
    //   delay(2000);

    //driveTurn2(-90);
      // driveArcRF(90, 450, 5000);
      // driveStraight2(600);

      
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
 
   // driveStraight2(100);
    
    // initializePath();
    // initializePathDistances();
    // purePursuitController();


     
      // while(true){
      // odometry2();
      // delay(5);
      // }
   // }

    odometry2();

    if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT)){
        intakeToggle = !intakeToggle;
    }

    if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT)){
        liftToggle = !liftToggle;
    }

  intake.set_value(intakeToggle);
      if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_A)){
        doinkerClampToggle = !doinkerClampToggle;
    }

  doinkerClamp.set_value(doinkerClampToggle);


    if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)){
        mogoToggle = !mogoToggle;
    }

  mogo.set_value(mogoToggle);

      if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_X)){
        doinkerToggle = !doinkerToggle;
    }

  doinker.set_value(doinkerToggle);
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
      con.print(1, 0, "prox: %f           ",float( OpticalC.get_proximity()));
    } else if (time % 150 == 0){
      con.print(2, 0, "C:%i H:%i LB:%i        ", int(chasstempC), int(HOOKS.get_temperature()), int(LadyBrown.get_temperature())); 
      // pros::lcd::print(1, "errorp:%f ", float(error));
    } 

	  	time += 1;
		  delay(1);
	  }
    
  }