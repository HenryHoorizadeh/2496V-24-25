#include "api.h"
// #include "auton.h"
#include "main.h"
#include "pid.h"
#include "robot.h"
#include "auton.h"
// #include "<valarray>"
// #include "<sstream>"
// #include "<string>"


using namespace pros;
using namespace c;
using namespace std;

//constants used for calculating power/voltage
double vKp;
double vKi;
double vKd;
float error; //amount from target
double prevError; //how is this specified/calculated??
double h;
int integral;
int derivative;
int time2;
double power; //voltage provided to motors at any given time to reach the target


//calc2
double vKp2;
double vKi2;
double vKd2;
float error2; //amount from target
double prevError2; //how is this specified/calculated??
double h2;
int integral2;
int derivative2;
int time22;
double power2;


void setConstants(double kp, double ki, double kd) {
    vKp = kp;
    vKi = ki;
    vKd = kd;
} 

void resetEncoders() { //reset the chassis motors every time a target is reached
    LF.tare_position(); //or set_zero_position(0) or set_zero_position(LF.get_position()); (sets current encoder position to 0)
    LB.tare_position();
	RF.tare_position();
	RB.tare_position();
    RM.tare_position();
	LM.tare_position();
}

//setting method for driving straight or turning (pos neg voltages change directions)
void chasMove(int voltageLF, int voltageLB, int voltageLM, int voltageRF, int voltageRB, int voltageRM) { //voltage to each chassis motor
    LF.move(voltageLF);
    LM.move(voltageLB);
    LB.move(voltageLB);
    RF.move(voltageRF);
    RM.move(voltageRF);
    RB.move(voltageRB);
}

int slew = 3;
double calcPID(double target, double input, int integralKi, int maxIntegral, bool slewOn) { //basically tuning i here
    int integral;
    prevError = error;
    error = target - input;
    
    if(abs(error) < integralKi) {
        integral += error;
    } else {
        integral = 0;
    }

    if(integral >= 0) {
        integral = min(integral, maxIntegral); //min means take whichever value is smaller btwn integral and maxI
        //integral = integral until integral is greater than maxI (to keep integral limited to maxI)
    } else {
        integral = max(integral, -maxIntegral); //same thing but negative max
    }

    
    derivative = error - prevError;

    power = (vKp * error) + (vKi * integral) + (vKd * derivative);

    return power;
} 



double calcPID2(double target, double input, int integralKi, int maxIntegral, bool slewOn) { //basically tuning i here
    int integral2;
    prevError2 = error2;
    error2 = target - input;
    
    if(std::abs(error2) < integralKi) {
        integral2 += error2;
    } else {
        integral2 = 0;
    }

    if(integral2 >= 0) {
        integral2 = std::min(integral2, maxIntegral); //min means take whichever value is smaller btwn integral and maxI
        //integral = integral until integral is greater than maxI (to keep integral limited to maxI)
    } else {
        integral2 = std::max(integral2, -maxIntegral); //same thing but negative max
    }
    integral2;
    
    derivative2 = error2 - prevError2;

    

    power2 = (vKp * error2) + (vKi * integral2) + (vKd * derivative2);

    return power2;
}

//driving straight
void driveStraight(int target) {


    double voltage;
    double encoderAvg;
    int count = 0;
    double init_heading = imu.get_heading();
    double heading_error = 0;
    int cycle = 0; // Controller Display Cycle
    time2 = 0;

    int timeout = 30000;
    double x = 0;
    x = double(abs(target));
    //timeout = (0 * pow(x,5)) + (0 * pow(x, 4)) + (0 * pow(x, 3)) + (0 * pow(x, 2)) + (0 * x) + 0; //Tune with Desmos
    imu.tare();
    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    resetEncoders();
    while(true) {

        encoderAvg = (LF.get_position() + RF.get_position()) / 2;
        voltage = calcPID(target, encoderAvg, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);

        
        //heading correction
        if(init_heading > 180) {
            init_heading = (360 - init_heading);
        }

        if(imu.get_heading() < 180) {
            heading_error = init_heading - imu.get_heading();
        } else {
            heading_error = ((360 - imu.get_heading()) - init_heading);
        }

        heading_error = heading_error * HEADING_CORRECTION_KP; 

        if(voltage > 127){
            voltage = 127;
        } else if (voltage < -127){
            voltage = -127;
        }

        chasMove( (voltage + heading_error ), (voltage + heading_error), (voltage + heading_error), (voltage - heading_error), (voltage - heading_error), (voltage - heading_error));
        if (abs(target - encoderAvg) <= 4) count++;
        if (count >= 20 || time2 > timeout){
            break;
        } 


      if (time2 % 50 == 0 && time2 % 100 != 0 && time2 != 150){
        con.print(0, 0, "ERROR: %f           ", float(error));
      } else if (time2 % 50 == 0 && time2 % 100 != 0){
        con.print(1, 0, "EncoderAvg: %f           ", float(encoderAvg));
      } else if (time2 % 50 == 0){
        con.print(2, 0, "Voltage: %f        ", float(voltage));
      } 

        delay(10);
        time2 += 10;
    }
    LF.brake();
    LM.brake();
    LB.brake();
    RF.brake();
    RM.brake();
    RB.brake();
}


//driving straight BUT GLOBAL
void driveStraight2(int target) {
    int timeout = 30000;
    double x = 0;
    x = double(abs(target));
    //timeout = (0 * pow(x,5)) + (0 * pow(x, 4)) + (0 * pow(x, 3)) + (0 * pow(x, 2)) + (0 * x) + 0; //Tune with Desmos
    
    double voltage;
    double encoderAvg;
    int count = 0;
    double init_heading = imu.get_heading();
    double heading_error = 0;
    int cycle = 0; // Controller Display Cycle
    time2 = 0;

    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    resetEncoders();
   

    while(true) {

        encoderAvg = (LF.get_position() + RF.get_position()) / 2;
        voltage = calcPID(target, encoderAvg, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);

        if(init_heading > 180) {
            init_heading = (360 - init_heading);
        }

        if(imu.get_heading() < 180) {
            heading_error = init_heading - imu.get_heading();
        }
        else {
            heading_error = ((360 - imu.get_heading()) - init_heading);
        }

        heading_error = heading_error * HEADING_CORRECTION_KP;
   
        if(voltage > 127){
            voltage = 127;
        } else if (voltage < -127){
            voltage = -127;
        }

        chasMove( (voltage + heading_error ), (voltage + heading_error), (voltage + heading_error), (voltage - heading_error), (voltage - heading_error), (voltage - heading_error));
        if (abs(target - encoderAvg) <= 4) count++;
        if (count >= 20 || time2 > timeout){
          break;
        } 

        if (time2 % 50 == 0 && time2 % 100 != 0 && time2 != 150){
          con.print(0, 0, "ERROR: %f           ", float(error));
        } else if (time2 % 50 == 0 && time2 % 100 != 0){
          con.print(1, 0, "EncoderAvg: %f           ", float(encoderAvg));
        } else if (time2 % 50 == 0){
          con.print(2, 0, "Voltage: %f        ", float(voltage));
        } 

        delay(10);
        time2 += 10;
        //hi
    }
    LF.brake();
    LM.brake();
    LB.brake();
    RF.brake();
    RM.brake();
    RB.brake();
}

// drive stright BUT GLOBAL AND WITH CHAINING (ends with velocity)
void driveStraightC(int target) {
    bool over = false;
    int timeout = 30000;
    double x = 0;
    x = double(abs(target));
    //timeout = (0 * pow(x,5)) + (0 * pow(x, 4)) + (0 * pow(x, 3)) + (0 * pow(x, 2)) + (0 * x) + 0; //Tune with Desmos

    if(target > 0){
        target = target + 500;
    } else {
        target = target - 500;
    }

    double voltage;
    double encoderAvg;
    int count = 0;
    double init_heading = imu.get_heading();
    double heading_error = 0;
    int cycle = 0; // Controller Display Cycle
    time2 = 0;

    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    resetEncoders();

    while(true) {

        encoderAvg = (LF.get_position() + RF.get_position()) / 2;
        voltage = calcPID(target, encoderAvg, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);

        if(init_heading > 180) {
            init_heading = (360 - init_heading);
        }

        if(imu.get_heading() < 180) {
            heading_error = init_heading - imu.get_heading();
        }
        else {
            heading_error = ((360 - imu.get_heading()) - init_heading);
        }

        heading_error = heading_error * HEADING_CORRECTION_KP;

        if(voltage > 127){
            voltage = 127;
        } else if (voltage < -127){
            voltage = -127;
        }

        chasMove( (voltage + heading_error ), (voltage + heading_error), (voltage + heading_error), (voltage - heading_error), (voltage - heading_error), (voltage - heading_error));
        if (target > 0){
            if ((encoderAvg - (target-500)) > 0){
                over = true;
            }
        } else {
             if (((target+500) - encoderAvg) > 0){
                over = true;
            }
        }

        if (over || time2 > timeout){
          break;
        } 

        if (time2 % 50 == 0 && time2 % 100 != 0 && time2 != 150){
          con.print(0, 0, "ERROR: %f           ", float(error));
        } else if (time2 % 50 == 0 && time2 % 100 != 0){
          con.print(1, 0, "EncoderAvg: %f           ", float(encoderAvg));
        } else if (time2 % 50 == 0){
          con.print(2, 0, "Voltage: %f        ", float(voltage));
        } 

        delay(10);
        time2 += 10;
        //hi
    }
}


//Turning
void driveTurn(int target) { //target is inputted in autons
    double voltage;
    double position;
    int count = 0;
    time2 = 0;
    int cycle = 0;

    setConstants(TURN_KP, TURN_KI, TURN_KD);

    int timeout = 30000;
    double variKP = 0;
    double variKD = 0;
    double x = 0;

    x = double(abs(target));
    variKP = (0 * pow(x,5)) + (0 * pow(x, 4)) + (0 * pow(x, 3)) + (0 * pow(x, 2)) + (0 * x) + 0; // Use Desmos to tune
    variKD = (0 * pow(x,5)) + (0 * pow(x, 4)) + (0 * pow(x, 3)) + (0 * pow(x, 2)) + (0 * x) + 0; // Use Desmos to tune
    //timeout = (0 * pow(x,5)) + (0 * pow(x, 4)) + (0 * pow(x, 3)) + (0 * pow(x, 2)) + (0 * x) + 0; // Use Desmos to tune

    //setConstants(variKP, TURN_KI, variKD); 

    imu.tare_heading();

    while(true) {

        position = imu.get_heading(); //this is where the units are set to be degrees

        if (position > 180) {
            position = ((360 - position) * -1 );
        }

        voltage = calcPID(target, position, TURN_INTEGRAL_KI, TURN_MAX_INTEGRAL, false);
        
        chasMove(voltage, voltage, voltage, -voltage, -voltage, -voltage);
        
        if (abs(target - position) <= 0.5) count++; 
        if (count >= 20 || time2 > timeout) {
           break; 
        }

        
        if (time2 % 50 == 0 && time2 % 100 != 0 && time2 != 150){
          con.print(0, 0, "ERROR: %f           ", float(error));
        } else if (time2 % 50 == 0 && time2 % 100 != 0){
          con.print(1, 0, "IMU: %f           ", float(imu.get_heading()));
        } else if (time2 % 50 == 0){
          con.print(2, 0, "Voltage: %f        ", float(voltage));
        } 

        time2 += 10;
        delay(10);
    }
    LF.brake();
    LM.brake();
    LB.brake();
    RF.brake();
    RM.brake();
    RB.brake();
}



//Turning BUT GLOBAL
void driveTurn2(int target) { //target is inputted in autons
    double voltage;
    double position;
    int count = 0;
    time2 = 0;
    int cycle = 0;
    int turnv = 0;

    position = imu.get_heading(); //this is where the units are set to be degrees

    if (position > 180){
        position = ((360 - position) * -1 );
    }

    if((target < 0) && (position > 0)){
        if((position - target) >= 180){
            target = target + 360;
            position = imu.get_heading();
            turnv = (target - position); // target + position
        } else {
             turnv = (abs(position) + abs(target));
        }
    } else if ((target > 0) && (position < 0)){
        if((target - position) >= 180){
           position = imu.get_heading();
            turnv = abs(abs(position) - abs(target));
        } else {
            turnv = (abs(position) + target);
        }
    } else {
         turnv = abs(abs(position) - abs(target));
    }

    //fortnite - derrick

    double variKP = 0;
    double x = 0;
    double variKD = 0;
    int timeout = 2100;

    x = double(abs(turnv));
    variKP = (0 * pow(x,5)) + (0 * pow(x, 4)) + (0 * pow(x, 3)) + (0 * pow(x, 2)) + (0 * x) + 0; // Use Desmos to tune
    variKD = (0 * pow(x,5)) + (0 * pow(x, 4)) + (0 * pow(x, 3)) + (0 * pow(x, 2)) + (0 * x) + 0; // Use Desmos to tune
    //timeout = (0 * pow(x,5)) + (0 * pow(x, 4)) + (0 * pow(x, 3)) + (0 * pow(x, 2)) + (0 * x) + 0; // Use Desmos to tune

    // setConstants(variKP, TURN_KI, variKD);


    while(true) {

        position = imu.get_heading(); 

        if (position > 180){
            position = ((360 - position) * -1 );
        }

        if((target < 0) && (position > 0)){
            if((position - target) >= 180){
                target = target + 360;
                position = imu.get_heading();
                turnv = (target - position); 
            } else {
                turnv = (abs(position) + abs(target));
            }
        } else if ((target > 0) && (position < 0)){
            if((target - position) >= 180){
            position = imu.get_heading();
                turnv = abs(abs(position) - abs(target));
            } else {
                turnv = (abs(position) + target);
            }
        } else {
            turnv = abs(abs(position) - abs(target));
        }

        voltage = calcPID(target, position, TURN_INTEGRAL_KI, TURN_MAX_INTEGRAL, false);

        
        chasMove(voltage, voltage, voltage, -voltage, -voltage, -voltage);
        
        if (abs(target - position) <= 0.5) count++; //0.35
        if (count >= 20 || time2 > timeout) {
           break; 
        }

        if (time2 % 50 == 0 && time2 % 100 != 0 && time2 != 150){
          con.print(0, 0, "ERROR: %f           ", float(error));
        } else if (time2 % 50 == 0 && time2 % 100 != 0){
          con.print(1, 0, "IMU: %f           ", float(imu.get_heading()));
        } else if (time2 % 50 == 0){
          con.print(2, 0, "Voltage: %f        ", float(voltage));
        } 

        time2 += 10;
        delay(10);
    }
    LF.brake();
    LM.brake();
    LB.brake();
    RF.brake();
    RM.brake();
    RB.brake();
}

void driveArcLF(double theta, double radius, int timeout){
    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);

    double ltarget = 0;
    double rtarget = 0;
    double ltargetFinal = 0;
    double rtargetFinal = 0;
    double pi =  3.14159265359;
    double init_heading = imu.get_heading();
    bool over = false;
    int count = 0;
    int time = 0;
    resetEncoders();
    con.clear();

    //int timeout = 5000;
    ltargetFinal = double((theta / 360) * 2 * pi * radius); // * double(2) * pi * double(radius));
    rtargetFinal = double((theta / 360) * 2 * pi * (radius + 550));
    theta = theta + 45;
    ltarget = double((theta / 360) * 2 * pi * radius); // * double(2) * pi * double(radius));
    rtarget = double((theta / 360) * 2 * pi * (radius + 550));
    while (true){

        double heading = imu.get_heading() - init_heading;

        if (theta > 0){
            if (heading > 30){
                heading = heading - 360;
            }
        } else {
            if (heading > 300){
                heading = heading - 360;
            }    
        }
        double encoderAvgL = LF.get_position();
        //encoderAvgL = 100;
        double encoderAvgR = (RB.get_position() +  RM.get_position()) / 2;

        int voltageL = calcPID(ltarget, encoderAvgL, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);
        // if(voltageL > 70){ //set left limit
        //     voltageL = 70;
        // } else if (voltageL < -70){
        //     voltageL = -70;
        // }
        int voltageR = calcPID(rtarget, encoderAvgR, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);
        // if(voltageR > 100){ // set right limit
        //     voltageR = 100;
        // } else if (voltageR < -100){
        //     voltageR = -100;
        // }

        double leftcorrect = (encoderAvgL * 360) / (2 * pi * radius);
        int fix = int(heading + leftcorrect);
        fix = fix * ARC_CORRECTION_KP;


        chasMove( (voltageL - fix), (voltageL - fix), (voltageL - fix), (voltageR + fix), (voltageR + fix), (voltageR + fix));

        if (radius > 0){
            if ((encoderAvgL - ltargetFinal) > 0){
                over = true;
            }
        } else {
            if ((ltargetFinal - encoderAvgL) > 0){
                over = true;
            }
        }

        if ((abs(ltarget - encoderAvgL) <= 4) && (abs(rtarget - encoderAvgR) <= 4)) count++;
        if (over || time > timeout){
            break;
        } 

        if (time2 % 50 == 0 && time2 % 100 != 0 && time2 != 150){
        con.print(0, 0, "ERROR: %f           ", float(error));
        } else if (time2 % 50 == 0 && time2 % 100 != 0){
        con.print(1, 0, "EncoderAvg: %f           ", float(encoderAvgL));
        } else if (time2 % 50 == 0){
        con.print(2, 0, "Voltage: %f        ", float(voltageL));
        } 

        time += 10;
        delay(10);

}
}

void driveArcL(double theta, double radius, int timeout){
    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);

    double ltarget = 0;
    double rtarget = 0;
    double pi =  3.14159265359;
    double init_heading = imu.get_heading();
    int count = 0;
    int time = 0;
    resetEncoders();
    con.clear();
    //int timeout = 5000;
    ltarget = double((theta / 360) * 2 * pi * radius); // * double(2) * pi * double(radius));
    rtarget = double((theta / 360) * 2 * pi * (radius + 550));

    while (true){

        double heading = imu.get_heading() - init_heading;
        if (theta > 0){
            if (heading > 30){
                heading = heading - 360;
            }
        } else {
            if (heading > 300){
                heading = heading - 360;
            }    
        }
        double encoderAvgL = LF.get_position();
        double encoderAvgR = (RB.get_position() +  RM.get_position()) / 2;
        int voltageL = calcPID(ltarget, encoderAvgL, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);
        // if(voltageL > 70){ //set left limit
        //     voltageL = 70;
        // } else if (voltageL < -70){
        //     voltageL = -70;
        // }
        int voltageR = calcPID(rtarget, encoderAvgR, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);
        // if(voltageR > 100){ //set right limit
        //     voltageR = 100;
        // } else if (voltageR < -100){
        //     voltageR = -100;
        // }

        double leftcorrect = (encoderAvgL * 360) / (2 * pi * radius);
        int fix = int(heading + leftcorrect);
        fix = fix * ARC_CORRECTION_KP;
    
        chasMove( (voltageL - fix), (voltageL - fix), (voltageL - fix), (voltageR + fix), (voltageR + fix), (voltageR + fix));
        if ((abs(ltarget - encoderAvgL) <= 4) && (abs(rtarget - encoderAvgR) <= 4)) count++;
        if (count >= 20 || time > timeout){
            break;
        } 

        if (time2 % 50 == 0 && time2 % 100 != 0 && time2 != 150){
        con.print(0, 0, "ERROR: %f           ", float(error));
        } else if (time2 % 50 == 0 && time2 % 100 != 0){
        con.print(1, 0, "EncoderAvg: %f           ", float(encoderAvgL));
        } else if (time2 % 50 == 0){
        con.print(2, 0, "Voltage: %f        ", float(voltageL));
        } 

        time += 10;
        delay(10);

    }
}






void driveArcR(double theta, double radius, int timeout){
    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);

    double ltarget = 0;
    double rtarget = 0;
    double pi =  3.14159265359;
    double init_heading = imu.get_heading();
    if (init_heading > 180){
        init_heading = init_heading - 360;
    }

    int count = 0;
    int time = 0;
    resetEncoders();
    con.clear();
    //int timeout = 5000;
    ltarget = double((theta / 360) * 2 * pi * (radius + 550)); // * double(2) * pi * double(radius));
    rtarget = double((theta / 360) * 2 * pi * (radius));
    while (true){



        double heading = imu.get_heading() - init_heading;
        if (theta > 0){
            if (heading > 300){
                heading = heading - 360;
            }
        } else {
            if (heading > 30){
                heading = heading - 360;
            }    
        }
        double encoderAvgL = LF.get_position();
        double encoderAvgR = (RB.get_position() +  RM.get_position()) / 2;
        int voltageL = calcPID(ltarget, encoderAvgL, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);
        // if(voltageL > 100){ //set left limit
        //     voltageL = 100;
        // } else if (voltageL < -100){
        //     voltageL = -100;
        // }
        int voltageR = calcPID(rtarget, encoderAvgR, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);
        // if(voltageR > 70){ //set right limit
        //     voltageR = 70;
        // } else if (voltageR < -70){
        //     voltageR = -70;
        // }

        double rightcorrect = (encoderAvgR * 360) / (2 * pi * radius);
        int fix = int(heading - rightcorrect);
        fix = fix * ARC_CORRECTION_KP;

        chasMove( (voltageL - fix), (voltageL - fix), (voltageL - fix), (voltageR + fix), (voltageR + fix), (voltageR + fix));
        if ((abs(ltarget - encoderAvgL) <= 4) && (abs(rtarget - encoderAvgR) <= 4)) count++;
        if (count >= 20 || time > timeout){
            break;
        } 

        if (time2 % 50 == 0 && time2 % 100 != 0 && time2 != 150){
        con.print(0, 0, "ERROR: %f           ", float(error));
        } else if (time2 % 50 == 0 && time2 % 100 != 0){
        con.print(1, 0, "EncoderAvg: %f           ", float(encoderAvgR));
        } else if (time2 % 50 == 0){
        con.print(2, 0, "Voltage: %f        ", float(voltageR));
        } 

        time += 10;
        delay(10);

}
}



void driveArcRF(double theta, double radius, int timeout){
    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    bool over = false;
    double ltarget = 0;
    double rtarget = 0;
    double ltargetFinal = 0;
    double rtargetFinal = 0;
    double pi =  3.14159265359;
    double init_heading = imu.get_heading();
    if (init_heading > 180){
        init_heading = init_heading - 360;
    }
    int count = 0;
    int time = 0;
    resetEncoders();
    con.clear();
    //int timeout = 5000;
    ltargetFinal = double((theta / 360) * 2 * pi * (radius+550)); // * double(2) * pi * double(radius));
    rtargetFinal = double((theta / 360) * 2 * pi * (radius));
    theta = theta + 45;
    ltarget = double((theta / 360) * 2 * pi * (radius + 550)); // * double(2) * pi * double(radius));
    rtarget = double((theta / 360) * 2 * pi * (radius));

    while (true){

        double heading = imu.get_heading() - init_heading;
        if (theta > 0){
            if (heading > 300){
                heading = heading - 360;
            }
        } else {
            if (heading > 30){
                heading = heading - 360;
            }    
        }
        double encoderAvgL = LF.get_position();
        double encoderAvgR = (RB.get_position() +  RM.get_position()) / 2;
        int voltageL = calcPID(ltarget, encoderAvgL, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);
        // if(voltageL > 100){ //set left limti
        //     voltageL = 100;
        // } else if (voltageL < -100){
        //     voltageL = -100;
        // }
        int voltageR = calcPID(rtarget, encoderAvgR, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);
        // if(voltageR > 70){ //set right limit
        //     voltageR = 70;
        // } else if (voltageR < -70){
        //     voltageR = -70;
        // }

        double rightcorrect = (encoderAvgR * 360) / (2 * pi * radius);
        int fix = int(heading - rightcorrect);
        fix = fix * ARC_CORRECTION_KP;

    

        chasMove( (voltageL - fix), (voltageL - fix), (voltageL - fix), (voltageR + fix), (voltageR + fix), (voltageR + fix));

        if (radius > 0){
            if ((encoderAvgR - (rtargetFinal)) > 0){
                over = true;
            }
        } else {
            if (((rtargetFinal) - encoderAvgR) > 0){
                over = true;
            }
        }

        if ((abs(ltarget - encoderAvgL) <= 4) && (abs(rtarget - encoderAvgR) <= 4)) count++;
        if (over || time > timeout){
            break;
        } 

        if (time2 % 50 == 0 && time2 % 100 != 0 && time2 != 150){
        con.print(0, 0, "ERROR: %f           ", float(error));
        } else if (time2 % 50 == 0 && time2 % 100 != 0){
        con.print(1, 0, "EncoderAvg: %f           ", float(encoderAvgR));
        } else if (time2 % 50 == 0){
        con.print(2, 0, "Voltage: %f        ", float(voltageR));
        } 

        time += 10;
        delay(10);

}
}
