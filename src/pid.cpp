#include "api.h"
// #include "auton.h"
#include "main.h"
#include "pid.h"
#include "robot.h"
#include "auton.h"
#include "odometry.h"
// #include "<valarray>"
// #include "<sstream>"
// #include "<string>"


using namespace pros;
using namespace c;
using namespace std;

bool mogoValues = false;
bool longValues = false;
bool stallProtection = false;
bool stalled = false;
int stallTime = 0;
int direc;
int direc2;
int hookpos;
int prevhookpos;
float view;
int stallC = 0;

double vKpl;
double vKil;
double vKdl;
float errorl; //amount from target
double prevErrorl; 
//double h;
int integrall; 
int derivativel;
int time2l;
double powerl;

//constants used for calculating power/voltage
double vKp;
double vKi;
double vKd;
float error; //amount from target
double prevError; 
//double h;
int integral; 
int derivative;
int time2;
double power; //voltage provided to motors at any given time to reach the target


//calc2
double vKp2;
double vKi2;
double vKd2;
float error2; //amount from target
double prevError2; 
double h2;
int integral2;
int derivative2;
int time22;
double power2;

//calc
double vKp3;
double vKi3;
double vKd3;
float error3; //amount from target
double prevError3; 
double h3;
int integral3;
int derivative3;
int time23;
double power3;

void hooks(int speed){
    direc = speed;
}

void intake2(int speed){
    direc2 = speed;
}

void stall(){


    //direc = hspeed;

    // if(sreverse){
    //     direc = -127;
    // } else {
    //     direc = 127;
    // }

    // if (reverse){
    //     direc = 127;
    // } else if(HOOKS.get_voltage() < -50) {
    //     direc = -127;
    // } else {
    //     direc = 0;
    // }

    // direc = HOOKS.get_voltage()/1000.0;

    if(stallProtection){
        prevhookpos = hookpos;
        hookpos = HOOKS.get_position();

        if((hookpos == prevhookpos)){
            stallC += 10;
        } else {
            stallC = 0;
        }

        if(stallC>100){
            stalled = true;
        }

        if (stalled){
            HOOKS.move(-direc);
            INTAKE.move(-direc2);
            stallTime += 10;
            if(stallTime >= 300){
                stalled = false;
                stallTime = 0;
            }
            view = 1;
        } else {
            HOOKS.move(direc);
            INTAKE.move(direc2);
            stallTime = 0;
            view = 0;
        }

        
    }
}


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
void chasMove(int voltageLF, int voltageLM, int voltageLB, int voltageRF, int voltageRM, int voltageRB) { //voltage to each chassis motor
    LF.move(voltageLF);
    LM.move(voltageLM);
    LB.move(voltageLB);
    RF.move(voltageRF);
    RM.move(voltageRM);
    RB.move(voltageRB);
}

int slew = 3;
double calcPID(double target, double input, int integralKi, int maxIntegral, bool slewOn) { //basically tuning i here
    odometry2();
    stall();
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
    
    derivative2 = error2 - prevError2;

    

    power2 = (vKp * error2) + (vKi * integral2) + (vKd * derivative2);

    return power2;
}


double calcPID3(double target, double input, int integralKi, int maxIntegral, bool slewOn) { //basically tuning i here
    int integral3;
    prevError3 = error3;
    error3 = target - input;
    
    if(std::abs(error3) < integralKi) {
        integral3 += error3;
    } else {
        integral3 = 0;
    }

    if(integral3 >= 0) {
        integral3 = std::min(integral3, maxIntegral); //min means take whichever value is smaller btwn integral and maxI
        //integral = integral until integral is greater than maxI (to keep integral limited to maxI)
    } else {
        integral3 = std::max(integral3, -maxIntegral); //same thing but negative max
    }
    
    derivative3 = error3 - prevError3;

    

    power3 = (vKp * error3) + (vKi * integral3) + (vKd * derivative3);

    return power3;
}

double calcPIDlift(double target, double input, int integralKi, int maxIntegral, int bias) { //basically tuning i here
    int integrall;
    prevErrorl = errorl;
    errorl = target - input;
    
    if(std::abs(errorl) < integralKi) {
        integrall += errorl;
    } else {
        integrall = 0;
    }

    if(integrall >= 0) {
        integrall = std::min(integrall, maxIntegral); //min means take whichever value is smaller btwn integral and maxI
        //integral = integral until integral is greater than maxI (to keep integral limited to maxI)
    } else {
        integrall = std::max(integrall, -maxIntegral); //same thing but negative max
    }
    
    derivativel = errorl - prevErrorl;

    powerl = (vKp * errorl) + (vKi * integrall) + (vKd * derivativel);
    
    //multiply only on the way up  
    // if(error < 0){
    //     powerl = powerl*bias;
    // }
    //multiply on the way up divide on the way down
    if(errorl < 0){
        powerl =  powerl*bias;
    } else {
        powerl = powerl/bias;
    }
    // straight add voltage to all scenarios 
    // powerl += bias;



    return powerl;
}





// void ColorSort(int color){
//     //blue color rejection
//     if (color == 0){
//         if(OpticalC.get_hue()<240 && OpticalC.get_hue()>180){
//             InitColor = true;
//         }

//         if (InitColor){
//             ColorCount += 1;
//         }

//         if(ColorCount > 105 && ColorCount < 800){
//             HOOKS.move(0);
//         } else {
//             HOOKS.move(127);
//         }
//         if(ColorCount>=800){
//             InitColor = false;
//             ColorCount = 0;
//         }


//     } else if (color == 1) { //red color rejectiom
//         if(OpticalC.get_hue()>0 && OpticalC.get_hue()<40){
//             InitColor = true;
//         } 

//         if (InitColor){
//             ColorCount += 1;
//         }

//         if(ColorCount > 110 && ColorCount < 800){
//             HOOKS.move(-30);
//         } else {
//             HOOKS.move(127);
//         }
//         if(ColorCount>=800){
//             InitColor = false;
//             ColorCount = 0;
//         }



// }
// }

// bool Backwards = false;
// void ColorSort(int color){
//     //blue color rejection
//     if (color == 0){
//         if(OpticalC.get_hue()<240 && OpticalC.get_hue()>180){
//             InitColor = true;
//         }

//         if (InitColor){
//             if(Backwards == false){
//                 HOOKS.move(127);
//                 if(HOOKS.get_position() > 500){
//                     Backwards = true; 
//                 }
//             } else {
//                 HOOKS.move(-127);
//                 if(HOOKS.get_position() < 200){
//                     Backwards = false;
//                     InitColor = false;
//                 }
//             }
//         } else {
//             HOOKS.move(127);
//             HOOKS.tare_position();
//         }






//     } else if (color == 1) { //red color rejectiom
//         if(OpticalC.get_hue()>0 && OpticalC.get_hue()<30){
//             InitColor = true;
//         } 

//         if (InitColor){
//             if(Backwards == false){
//                 HOOKS.move(127);
//                 if(HOOKS.get_position() > 610){
//                     Backwards = true; 
//                 }
//             } else {
//                 HOOKS.move(-127);
//                 if(HOOKS.get_position() < -200){
//                     Backwards = false;
//                     InitColor = false;
//                 }
//             }
//         } else {
//             HOOKS.move(50);
//             HOOKS.tare_position();
//         }



// }
// }

bool InitColor = false;
bool InitCorrect = false;
int ColorCount;
bool Backwards = false;
void ColorSort(int color){
    //blue color rejection
    if (color == 0){
        if(OpticalC.get_hue()<240 && OpticalC.get_hue()>180){
            InitColor = true;
        }

        if (InitColor){
            if(Backwards == false){
                HOOKS.move(127);
                if(HOOKS.get_position() > 500){
                    Backwards = true; 
                }
            } else {
                HOOKS.move(-127);
                if(HOOKS.get_position() < 200){
                    Backwards = false;
                    InitColor = false;
                }
            }
        } else {
            HOOKS.move(127);
            HOOKS.tare_position();
        }






    } else if (color == 1) { //red color rejectiom
        if(OpticalC.get_hue()>0 && OpticalC.get_hue()<30){
            InitColor = true;
        } 

        if(OpticalC.get_hue()<240 && OpticalC.get_hue()>180){
            InitCorrect = true;
        }

        if (InitColor){
            if(Backwards == false){
                HOOKS.move(-127);
                if(OpticalC.get_hue()<240 && OpticalC.get_hue()>180){
                    INTAKE.move(0);
                } else {
                    INTAKE.move(60);
                }
                if(HOOKS.get_position() < -3000){
                    Backwards = true; 
                }
            } else {
                INTAKE.move(127);
                HOOKS.move(127);
                Backwards = false;
                InitColor = false;
            }
        } else if(InitCorrect){
            if(Backwards == false){
                HOOKS.move(127);
                if(OpticalC.get_hue()>0 && OpticalC.get_hue()<30){
                    INTAKE.move(0);
                } else {
                    INTAKE.move(60);
                }
                if(HOOKS.get_position() > 4000){
                    Backwards = true; 
                }
            } else {
                INTAKE.move(127);
                HOOKS.move(-127);
                Backwards = false;
                InitColor = false;
            }

        } else {

            INTAKE.move(127);
            HOOKS.move(127);
            HOOKS.tare_position();
        }



}
}



//driving straight
void driveStraight(int target) {

    imu.tare();
    double voltage;
    double encoderAvg;
    int count = 0;
    double init_heading = imu.get_heading();
    double heading_error = 0;
    int cycle = 0; // Controller Display Cycle
    time2 = 0;

    if (init_heading > 180){
        init_heading = init_heading - 360;
    }

    int timeout = 30000;
    double x = 0;
    x = double(abs(target));

    timeout = (0.00000000000014342 * pow(x,5)) + (-0.0000000010117 * pow(x, 4)) + (0.0000025601 * pow(x, 3)) + (-0.002955 * pow(x, 2)) + (2.15494 * x) + 361.746; //Tune with Desmos

    resetEncoders();
    while(true) {
        ColorSort(RingColor);
        
        setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
        encoderAvg = (LF.get_position() + RF.get_position()) / 2;
        voltage = calcPID(target, encoderAvg, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);

        

        double position = imu.get_heading(); //this is where the units are set to be degrees

        if (position > 180){
            position = position - 360;
        }

        if((init_heading < 0) && (position > 0)){
            if((position - init_heading) >= 180){
                init_heading = init_heading + 360;
                position = imu.get_heading();
            } 
        } else if ((init_heading > 0) && (position < 0)){
            if((init_heading - position) >= 180){
            position = imu.get_heading();
            }
        } 
        if(longValues){
            setConstants(HEADING_KP2, HEADING_KI2, HEADING_KD2);
        } else {
            setConstants(HEADING_KP, HEADING_KI, HEADING_KD);
        }
        heading_error = calcPID2(init_heading, position, HEADING_INTEGRAL_KI, HEADING_MAX_INTEGRAL, true);


        if(voltage > 127){
            voltage = 127;
        } else if (voltage < -127){
            voltage = -127;
        }
        errorp = abs(target - encoderAvg);
        chasMove( (voltage + heading_error ), (voltage + heading_error), (voltage + heading_error), (voltage - heading_error), (voltage - heading_error), (voltage - heading_error));
        if (abs(target - encoderAvg) <= 3) count++;
        if (count >= 20 || time2 > timeout){
            break;
        } 

        if (time2 % 50 == 0 && time2 % 100 != 0 && time2 % 150 != 0){
            con.print(0, 0, "ERROR: %f           ", float(error));
        } else if (time2 % 100 == 0 && time2 % 150 != 0){
            con.print(1, 0, "EncoderAvg: %f           ", float(encoderAvg));
        } else if (time2 % 150 == 0){
            con.print(2, 0, "Time: %f        ", float(time2));
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
void driveClamp(int target, int clampDistance) {
    int timeout = 30000;
    double x = 0;
    x = double(abs(target));
     timeout = (0.00000000000014342 * pow(x,5)) + (-0.0000000010117 * pow(x, 4)) + (0.0000025601 * pow(x, 3)) + (-0.002955 * pow(x, 2)) + (2.15494 * x) + 361.746; //Tune with Desmos

    bool over = false;
    double voltage;
    double encoderAvg;
    int count = 0;
    double init_heading = imu.get_heading();
    double heading_error = 0;
    int cycle = 0; // Controller Display Cycle
    time2 = 0;

    if(init_heading > 180){
        init_heading = init_heading - 360;
    }

    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    resetEncoders();
   

    while(true) {
    ColorSort(RingColor);

    encoderAvg = (LF.get_position() + RF.get_position()) / 2;
    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    voltage = calcPID(target, encoderAvg, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);


    double position = imu.get_heading(); //this is where the units are set to be degrees

    if (position > 180){
        position = position - 360;
    }

    if((init_heading < 0) && (position > 0)){
        if((position - init_heading) >= 180){
            init_heading = init_heading + 360;
            position = imu.get_heading();
        } 
    } else if ((init_heading > 0) && (position < 0)){
        if((init_heading - position) >= 180){
           position = imu.get_heading();
        }
    } 


        // if(init_heading > 180) {
        //     init_heading = (360 - init_heading);
        // }

        // if(imu.get_heading() < 180) {
        //     heading_error = init_heading - imu.get_heading();
        // }
        // else {
        //     heading_error = ((360 - imu.get_heading()) - init_heading);
        // }

        // heading_error = heading_error * HEADING_CORRECTION_KP;

        if(longValues){
            setConstants(HEADING_KP2, HEADING_KI2, HEADING_KD2);
        } else {
            setConstants(HEADING_KP, HEADING_KI, HEADING_KD);
        }

        heading_error = calcPID2(init_heading, position, HEADING_INTEGRAL_KI, HEADING_MAX_INTEGRAL, true);
   
        if(voltage > 127){
            voltage = 127;
        } else if (voltage < -127){
            voltage = -127;
        }

        if(abs(error) < clampDistance){
            mogo.set_value(true);
        }



        chasMove( (voltage + heading_error ), (voltage + heading_error), (voltage + heading_error), (voltage - heading_error), (voltage - heading_error), (voltage - heading_error));
        if (abs(target - encoderAvg) <= 4) count++;
        if (count >= 20 || time2 > timeout){
            break;
        } 


        if (time2 % 50 == 0 && time2 % 100 != 0 && time2 % 150 != 0){
            con.print(0, 0, "ERROR: %f           ", float(error));
        } else if (time2 % 100 == 0 && time2 % 150 != 0){
            con.print(1, 0, "EncoderAvg: %f           ", float(encoderAvg));
        } else if (time2 % 150 == 0){
            con.print(2, 0, "Time: %f        ", float(time2));
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


void driveClampS(int target, int clampDistance, int speed) {
    int timeout = 30000;
    double x = 0;
    x = double(abs(target));
     timeout = (0.00000000000014342 * pow(x,5)) + (-0.0000000010117 * pow(x, 4)) + (0.0000025601 * pow(x, 3)) + (-0.002955 * pow(x, 2)) + (2.15494 * x) + 361.746; //Tune with Desmos
    timeout = timeout*((1.0-(speed/100.0))+1.0);
    bool over = false;
    double voltage;
    double encoderAvg;
    int count = 0;
    double init_heading = imu.get_heading();
    double heading_error = 0;
    int cycle = 0; // Controller Display Cycle
    time2 = 0;

    if(init_heading > 180){
        init_heading = init_heading - 360;
    }

    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    resetEncoders();
   

    while(true) {
    ColorSort(RingColor);
    encoderAvg = (LF.get_position() + RF.get_position()) / 2;
    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    voltage = calcPID(target, encoderAvg, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);


    double position = imu.get_heading(); //this is where the units are set to be degrees

    if (position > 180){
        position = position - 360;
    }

    if((init_heading < 0) && (position > 0)){
        if((position - init_heading) >= 180){
            init_heading = init_heading + 360;
            position = imu.get_heading();
        } 
    } else if ((init_heading > 0) && (position < 0)){
        if((init_heading - position) >= 180){
           position = imu.get_heading();
        }
    } 


        // if(init_heading > 180) {
        //     init_heading = (360 - init_heading);
        // }

        // if(imu.get_heading() < 180) {
        //     heading_error = init_heading - imu.get_heading();
        // }
        // else {
        //     heading_error = ((360 - imu.get_heading()) - init_heading);
        // }

        // heading_error = heading_error * HEADING_CORRECTION_KP;

        if(longValues){
            setConstants(HEADING_KP2, HEADING_KI2, HEADING_KD2);
        } else {
            setConstants(HEADING_KP, HEADING_KI, HEADING_KD);
        }

        heading_error = calcPID2(init_heading, position, HEADING_INTEGRAL_KI, HEADING_MAX_INTEGRAL, true);
   
        // if(voltage > 127){
        //     voltage = 127;
        // } else if (voltage < -127){
        //     voltage = -127;
        // }

        if(abs(error) < clampDistance){
            mogo.set_value(true);
        }

        if(voltage > 127 * double(speed)/100.0){
            voltage = 127 * double(speed)/100.0;
        } else if (voltage < -127 * double(speed)/100.0){
             voltage = -127 * double(speed)/100.0;
        }


        chasMove( (voltage + heading_error ), (voltage + heading_error), (voltage + heading_error), (voltage - heading_error), (voltage - heading_error), (voltage - heading_error));
        if (abs(target - encoderAvg) <= 4) count++;
        if (count >= 20 || time2 > timeout){
            break;
        } 


        if (time2 % 50 == 0 && time2 % 100 != 0 && time2 % 150 != 0){
            con.print(0, 0, "ERROR: %f           ", float(error));
        } else if (time2 % 100 == 0 && time2 % 150 != 0){
            con.print(1, 0, "Voltage: %f           ", float(double(speed)/100.0));
        } else if (time2 % 150 == 0){
            con.print(2, 0, "Time: %f        ", float(time2));
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

void driveStraight2(int target) {
    int timeout = 30000;
    double x = 0;
    x = double(abs(target));
     timeout = (0.00000000000014342 * pow(x,5)) + (-0.0000000010117 * pow(x, 4)) + (0.0000025601 * pow(x, 3)) + (-0.002955 * pow(x, 2)) + (2.15494 * x) + 301.746; //361.746 //Tune with Desmos

    bool over = false;
    double voltage;
    double encoderAvg;
    int count = 0;
    double init_heading = imu.get_heading();
    double heading_error = 0;
    int cycle = 0; // Controller Display Cycle
    time2 = 0;

    if(init_heading > 180){
        init_heading = init_heading - 360;
    }

    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    resetEncoders();
   

    while(true) {

    ColorSort(RingColor);
    encoderAvg = (LF.get_position() + RF.get_position()) / 2;
    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    voltage = calcPID(target, encoderAvg, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);


    double position = imu.get_heading(); //this is where the units are set to be degrees

    if (position > 180){
        position = position - 360;
    }

    if((init_heading < 0) && (position > 0)){
        if((position - init_heading) >= 180){
            init_heading = init_heading + 360;
            position = imu.get_heading();
        } 
    } else if ((init_heading > 0) && (position < 0)){
        if((init_heading - position) >= 180){
           position = imu.get_heading();
        }
    } 


        // if(init_heading > 180) {
        //     init_heading = (360 - init_heading);
        // }

        // if(imu.get_heading() < 180) {
        //     heading_error = init_heading - imu.get_heading();
        // }
        // else {
        //     heading_error = ((360 - imu.get_heading()) - init_heading);
        // }

        // heading_error = heading_error * HEADING_CORRECTION_KP;

        if(longValues){
            setConstants(HEADING_KP2, HEADING_KI2, HEADING_KD2);
        } else {
            setConstants(HEADING_KP, HEADING_KI, HEADING_KD);
        }

        heading_error = calcPID2(init_heading, position, HEADING_INTEGRAL_KI, HEADING_MAX_INTEGRAL, true);
   
        if(voltage > 127){
            voltage = 127;
        } else if (voltage < -127){
            voltage = -127;
        }

        chasMove( (voltage + heading_error ), (voltage + heading_error), (voltage + heading_error), (voltage - heading_error), (voltage - heading_error), (voltage - heading_error));
        if (abs(target - encoderAvg) <= 4) count++;
        if (count >= 8 || time2 > timeout){
            break;
        } 


        if (time2 % 50 == 0 && time2 % 100 != 0 && time2 % 150 != 0){
            con.print(0, 0, "ERROR: %f           ", float(error));
        } else if (time2 % 100 == 0 && time2 % 150 != 0){
            con.print(1, 0, "EncoderAvg: %f           ", float(encoderAvg));
        } else if (time2 % 150 == 0){
            con.print(2, 0, "Time: %f        ", float(time2));
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
     timeout = (0.00000000000014342 * pow(x,5)) + (-0.0000000010117 * pow(x, 4)) + (0.0000025601 * pow(x, 3)) + (-0.002955 * pow(x, 2)) + (2.15494 * x) + 361.746; //Tune with Desmos

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

    if(init_heading > 180){
        init_heading = init_heading - 360;
    }

    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    resetEncoders();

    while(true) {
        ColorSort(RingColor);
        encoderAvg = (LF.get_position() + RF.get_position()) / 2;
        setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
        voltage = calcPID(target, encoderAvg, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);

    
        double position = imu.get_heading(); //this is where the units are set to be degrees

        if (position > 180){
            position = position - 360;
        }

        if((init_heading < 0) && (position > 0)){
            if((position - init_heading) >= 180){
                init_heading = init_heading + 360;
                position = imu.get_heading();
            } 
        } else if ((init_heading > 0) && (position < 0)){
            if((init_heading - position) >= 180){
            position = imu.get_heading();
            }
        } 
    

        // if(init_heading > 180) {
        //     init_heading = (360 - init_heading);
        // }

        // if(imu.get_heading() < 180) {
        //     heading_error = init_heading - imu.get_heading();
        // }
        // else {
        //     heading_error = ((360 - imu.get_heading()) - init_heading);
        // }

        setConstants(HEADING_KP, HEADING_KI, HEADING_KD);
        heading_error = calcPID2(init_heading, position, HEADING_INTEGRAL_KI, HEADING_MAX_INTEGRAL, true);

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

        if (time2 % 50 == 0 && time2 % 100 != 0 && time2 % 150 != 0){
            con.print(0, 0, "ERROR: %f           ", float(error));
        } else if (time2 % 100 == 0 && time2 % 150 != 0){
            con.print(1, 0, "EncoderAvg: %f           ", float(encoderAvg));
        } else if (time2 % 150 == 0){
            con.print(2, 0, "Time: %f        ", float(time2));
        } 

        delay(10);
        time2 += 10;
        //hi
    }
}


void driveStraightSlow(int target, int speed) {
    int timeout = 30000;
    double x = 0;
    x = double(abs(target));
     timeout = (0.00000000000014342 * pow(x,5)) + (-0.0000000010117 * pow(x, 4)) + (0.0000025601 * pow(x, 3)) + (-0.002955 * pow(x, 2)) + (2.15494 * x) + 301.746; //361.746 //Tune with Desmos


    timeout = timeout*((1.0-(speed/100.0))+1.0);
    bool over = false;
    double voltage;
    double encoderAvg;
    int count = 0;
    double init_heading = imu.get_heading();
    double heading_error = 0;
    int cycle = 0; // Controller Display Cycle
    time2 = 0;

    if(init_heading > 180){
        init_heading = init_heading - 360;
    }

    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    resetEncoders();
   

    while(true) {

    ColorSort(RingColor);
    encoderAvg = (LF.get_position() + RF.get_position()) / 2;
    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    voltage = calcPID(target, encoderAvg, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);


    double position = imu.get_heading(); //this is where the units are set to be degrees

    if (position > 180){
        position = position - 360;
    }

    if((init_heading < 0) && (position > 0)){
        if((position - init_heading) >= 180){
            init_heading = init_heading + 360;
            position = imu.get_heading();
        } 
    } else if ((init_heading > 0) && (position < 0)){
        if((init_heading - position) >= 180){
           position = imu.get_heading();
        }
    } 


        // if(init_heading > 180) {
        //     init_heading = (360 - init_heading);
        // }

        // if(imu.get_heading() < 180) {
        //     heading_error = init_heading - imu.get_heading();
        // }
        // else {
        //     heading_error = ((360 - imu.get_heading()) - init_heading);
        // }

        // heading_error = heading_error * HEADING_CORRECTION_KP;

        
        if(longValues){
            setConstants(HEADING_KP2, HEADING_KI2, HEADING_KD2);
        } else {
            setConstants(HEADING_KP, HEADING_KI, HEADING_KD);
        }
        
        heading_error = calcPID2(init_heading, position, HEADING_INTEGRAL_KI, HEADING_MAX_INTEGRAL, true);
   

        if(voltage > 127 * double(speed)/100.0){
            voltage = 127 * double(speed)/100.0;
        } else if (voltage < -127 * double(speed)/100.0){
             voltage = -127 * double(speed)/100.0;
        }


        chasMove( (voltage + heading_error ), (voltage + heading_error), (voltage + heading_error), (voltage - heading_error), (voltage - heading_error), (voltage - heading_error));
        if (abs(target - encoderAvg) <= 4) count++;
        if (count >= 8 || time2 > timeout){
            break;
        } 


        if (time2 % 50 == 0 && time2 % 100 != 0 && time2 % 150 != 0){
            con.print(0, 0, "ERROR: %f           ", float(error));
        } else if (time2 % 100 == 0 && time2 % 150 != 0){
            con.print(1, 0, "EncoderAvg: %f           ", float(encoderAvg));
        } else if (time2 % 150 == 0){
            con.print(2, 0, "Time: %f        ", float(time2));
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



//Turning
void driveTurn(int target) { //target is inputted in autons
    double voltage;
    double position;
    int count = 0;
    time2 = 0;


    setConstants(TURN_KP, TURN_KI, TURN_KD);

    int timeout = 30000;
    double variKP = 0;
    double variKD = 0;
    double x = 0;

    x = double(abs(target));
   // variKP = (0 * pow(x,5)) + (0 * pow(x, 4)) + (0 * pow(x, 3)) + (0 * pow(x, 2)) + (0 * x) + 0; // Use Desmos to tune
   variKD =( -0.0000000090021 * pow(x,5)) + (0.0000034017 * pow(x, 4)) + (-0.000428205 * pow(x, 3)) + (0.0214316 * pow(x, 2)) + (-0.351622 * x) + 94.6899; // Use Desmos to tune
   if(mogoValues){
    //variKD =(-0.0000000042528 * pow(x,5)) + (0.00000209186 * pow(x, 4)) + (-0.000381218 * pow(x, 3)) + (0.0314888 * pow(x, 2)) + (-0.951821 * x) + 87.7549; // Use Desmos to tune
    variKD =(0.00000000982635 * pow(x,5)) + (-0.00000354451 * pow(x, 4)) + (0.000379494 * pow(x, 3)) + (-0.00861751 * pow(x, 2)) + (-0.151957 * x) + 96.4185; // Use Desmos to tune
   } 
    timeout = (0.000000034029 * pow(x,5)) + (-0.0000208972 * pow(x, 4)) + (0.0042105 * pow(x, 3)) + (-0.334536 * pow(x, 2)) + (13.1348 * x) + 399.116; // Use Desmos to tune
    if(abs(target>=25)){
    setConstants(TURN_KP, TURN_KI, variKD); 
    } else if(mogoValues == false) {
    setConstants(5, TURN_KI, 90); 
    }

    imu.tare_heading();

    while(true) {
        ColorSort(RingColor);
        position = imu.get_heading(); //this is where the units are set to be degrees

        if (position > 180) {
            position = position - 360;
        }

        voltage = calcPID(target, position, TURN_INTEGRAL_KI, TURN_MAX_INTEGRAL, false);
        
        chasMove(voltage, voltage, voltage, -voltage, -voltage, -voltage);
        //errorp = abs(target - position);
        if (abs(target - position) <= 0.5) count++; 
        if (count >= 20 || time2 > timeout) {
            errorp = error;
          break; 
        }

        
        if (time2 % 50 == 0 && time2 % 100 != 0 && time2 % 150 != 0){
            con.print(0, 0, "ERROR: %f           ", float(error));
        } else if (time2 % 100 == 0 && time2 % 150 != 0){
            con.print(1, 0, "IMU: %f           ", float(imu.get_heading()));
        } else if (time2 % 150 == 0){
            con.print(2, 0, "Time: %f        ", float(time2));
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
   // variKP = (0 * pow(x,5)) + (0 * pow(x, 4)) + (0 * pow(x, 3)) + (0 * pow(x, 2)) + (0 * x) + 0; // Use Desmos to tune
   variKD =( -0.0000000090021 * pow(x,5)) + (0.0000034017 * pow(x, 4)) + (-0.000428205 * pow(x, 3)) + (0.0214316 * pow(x, 2)) + (-0.351622 * x) + 94.6899; // Use Desmos to tune
   if(mogoValues){
    //variKD =(-0.0000000042528 * pow(x,5)) + (0.00000209186 * pow(x, 4)) + (-0.000381218 * pow(x, 3)) + (0.0314888 * pow(x, 2)) + (-0.951821 * x) + 87.7549; // Use Desmos to tune
    variKD =(0.00000000982635 * pow(x,5)) + (-0.00000354451 * pow(x, 4)) + (0.000379494 * pow(x, 3)) + (-0.00861751 * pow(x, 2)) + (-0.151957 * x) + 96.4185; // Use Desmos to tune
   } 
    timeout = (0.000000034029 * pow(x,5)) + (-0.0000208972 * pow(x, 4)) + (0.0042105 * pow(x, 3)) + (-0.334536 * pow(x, 2)) + (13.1348 * x) + 399.116; // Use Desmos to tune
    if(abs(turnv)>=25){
    setConstants(TURN_KP, TURN_KI, variKD); 
    } else if(mogoValues == false) {
    setConstants(5, TURN_KI, 90); 
    }

//     x = double(abs(turnv));
//    // variKP = (0 * pow(x,5)) + (0 * pow(x, 4)) + (0 * pow(x, 3)) + (0 * pow(x, 2)) + (0 * x) + 0; // Use Desmos to tune
//      //variKD =( -0.0000000090021 * pow(x,5)) + (0.0000034017 * pow(x, 4)) + (-0.000428205 * pow(x, 3)) + (0.0214316 * pow(x, 2)) + (-0.351622 * x) + 128.6899;
//      variKD =(-0.0000000042528 * pow(x,5)) + (0.00000209186 * pow(x, 4)) + (-0.000381218 * pow(x, 3)) + (0.0314888 * pow(x, 2)) + (-0.951821 * x) + 97.7549; // Use Desmos to tune //94.6899
//    if(mogoValues){
//     variKD =(-0.0000000042528 * pow(x,5)) + (0.00000209186 * pow(x, 4)) + (-0.000381218 * pow(x, 3)) + (0.0314888 * pow(x, 2)) + (-0.951821 * x) + 97.7549; // Use Desmos to tune
//    } 
//     timeout = (0.000000034029 * pow(x,5)) + (-0.0000208972 * pow(x, 4)) + (0.0042105 * pow(x, 3)) + (-0.334536 * pow(x, 2)) + (13.1348 * x) + 399.116; // Use Desmos to tune

//     setConstants(TURN_KP, TURN_KI, variKD); 



    while(true) {
        ColorSort(RingColor);
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
            errorp=error;
           break; 
        }

        if (time2 % 50 == 0 && time2 % 100 != 0 && time2 % 150 != 0){
            con.print(0, 0, "ERROR: %f           ", float(error));
        } else if (time2 % 100 == 0 && time2 % 150 != 0){
            con.print(1, 0, "IMU: %f           ", float(imu.get_heading()));
        } else if (time2 % 150 == 0){
            con.print(2, 0, "mogoValues: %f        ", float(mogoValues));
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
    int trueTheta = theta;
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
    rtargetFinal = double((theta / 360) * 2 * pi * (radius + 390));
    if(theta > 0){
        theta = theta + 45;
    } else {
        theta = theta - 45; 
    }
    ltarget = double((theta / 360) * 2 * pi * radius); // * double(2) * pi * double(radius));
    rtarget = double((theta / 360) * 2 * pi * (radius + 390));
    while (true){
        ColorSort(RingColor);

        double encoderAvgL = LF.get_position();
        double encoderAvgR = (RB.get_position() +  RM.get_position()) / 2;
        double leftcorrect = -(encoderAvgL * 360) / (2 * pi * radius);

        if(init_heading > 180){
            init_heading = init_heading - 360;
        }

        double position = imu.get_heading(); //this is where the units are set to be degrees W

        if (position > 180){
            position = position - 360;
        }

        if(((init_heading + leftcorrect)< 0) && (position > 0)){
            if((position - (init_heading + leftcorrect)) >= 180){
                leftcorrect = leftcorrect + 360;
                position = imu.get_heading();
            } 
        } else if (((init_heading + leftcorrect) > 0) && (position < 0)){
            if(((init_heading + leftcorrect) - position) >= 180){
            position = imu.get_heading();
            }
        } 
    


        setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
        int voltageL = calcPID(ltarget, encoderAvgL, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);
        // if(voltageL > 70){ //set left limit
        //     voltageL = 70;
        // } else if (voltageL < -70){
        //     voltageL = -70;
        // }
        int voltageR = calcPID2(rtarget, encoderAvgR, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);
        // if(voltageR > 100){ // set right limit
        //     voltageR = 100;
        // } else if (voltageR < -100){
        //     voltageR = -100;
        // }
    

        setConstants(ARC_HEADING_KP, ARC_HEADING_KI, ARC_HEADING_KD);
        int fix = calcPID3((init_heading + leftcorrect), position, ARC_HEADING_INTEGRAL_KI, ARC_HEADING_MAX_INTEGRAL, true);


        chasMove( (voltageL + fix), (voltageL + fix), (voltageL + fix), (voltageR - fix), (voltageR - fix), (voltageR - fix));

        // if (theta > 0){
        //     if ((encoderAvgL - ltargetFinal) > 0){
        //         over = true;
        //     }
        // } else {
        //     if ((ltargetFinal - encoderAvgL) > 0){
        //         over = true;
        //     }
        // }

        if(abs((init_heading - position)) > trueTheta){
            over = true;
        }

        if (over || time > timeout){
            break;
        } 

        if (time2 % 50 == 0 && time2 % 100 != 0 && time2 % 150 != 0){
            con.print(0, 0, "ERROR: %f           ", float(error));
        } else if (time2 % 100 == 0 && time2 % 150 != 0){
            con.print(1, 0, "EncoderL: %f           ", float(encoderAvgL));
        } else if (time2 % 150 == 0){
            con.print(2, 0, "Theta: %f        ", float(abs((init_heading + leftcorrect) - position)));
        } 

        time += 10;
        delay(10);

}
}

void driveArcL(double theta, double radius, int timeout){
    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);

    //int timeout = 30000;

    double totalError = 0;

    double ltarget = 0;
    double rtarget = 0;
    double pi = 3.14159265359;
    double init_heading = imu.get_heading();
    int count = 0;
    time2 = 0;
    resetEncoders();
    con.clear();
    //int timeout = 5000;
    ltarget = double((theta / 360) * 2 * pi * radius); 
    rtarget = double((theta / 360) * 2 * pi * (radius + 390));

    while (true){
        ColorSort(RingColor);
        double encoderAvgL = (LF.get_position() + LB.get_position()) / 2;
        double encoderAvgR = (RF.get_position() +  RB.get_position()) / 2;
        double leftcorrect = -(encoderAvgL * 360) / (2 * pi * radius);

        if(init_heading > 180){
            init_heading = init_heading - 360;
        }

        double position = imu.get_heading(); //this is where the units are set to be degrees W

        if (position > 180){
            position = position - 360;
        }

        if((leftcorrect < 0) && (position > 0)){
            if((position - leftcorrect) >= 180){
                leftcorrect = leftcorrect + 360;
                position = imu.get_heading();
            } 
        } else if ((leftcorrect > 0) && (position < 0)){
            if((leftcorrect - position) >= 180){
            position = imu.get_heading();
            }
        } 
    
        setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
        int voltageL = calcPID(ltarget, encoderAvgL, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);
        if(voltageL > 127){ //set left limit
            voltageL = 127;
        } else if (voltageL < -127){
            voltageL = -127;
        }

        int voltageR = calcPID2(rtarget, encoderAvgR, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);
        if(voltageR > 127){ //set right limit
            voltageR = 127;
        } else if (voltageR < -127){
            voltageR = -127;
        }
        //cole is just better. 8838D is king! :}
  

        setConstants(ARC_HEADING_KP, ARC_HEADING_KI, ARC_HEADING_KD);
        int fix = calcPID3((init_heading + leftcorrect), position, ARC_HEADING_INTEGRAL_KI, ARC_HEADING_MAX_INTEGRAL, true);
        totalError += error3;
    
        chasMove((voltageL + fix), (voltageL + fix), (voltageL + fix), (voltageR - fix), (voltageR - fix), (voltageR - fix));
        if ((abs(ltarget - encoderAvgL) <= 4) && (abs(rtarget - encoderAvgR) <= 4)) count++;
        if (count >= 20 || time2 > timeout){
          //  break;
        } 

        if (time2 % 50 == 0 && time2 % 100 != 0 && time2 % 150 != 0){
            con.print(0, 0, "ERROR: %f           ", float(error));
        } else if (time2 % 100 == 0 && time2 % 150 != 0){
            con.print(1, 0, "fix: %f           ", float(fix));
        } else if (time2 % 150 == 0){
            con.print(2, 0, "Time: %f        ", float(time2));
        } 

        time2 += 10;
        delay(10);

    }
    
}






void driveArcR(double theta, double radius, int timeout){
    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);

    double ltarget = 0;
    double rtarget = 0;
    double pi =  3.14159265359;
    double init_heading = imu.get_heading();
    // if (init_heading > 180){
    //     init_heading = init_heading - 360;
    // }

    int count = 0;
    int time = 0;
    resetEncoders();
    con.clear();
    //int timeout = 5000;
    ltarget = double((theta / 360) * 2 * pi * (radius + 390)); // * double(2) * pi * double(radius));
    rtarget = double((theta / 360) * 2 * pi * (radius));
    while (true){
        ColorSort(RingColor);
        double encoderAvgL = (LF.get_position() + LB.get_position()) / 2;
        double encoderAvgR = (RB.get_position() +  RB.get_position()) / 2;
        double rightcorrect = (encoderAvgR * 360) / (2 * pi * radius);

        if(init_heading > 180){
            init_heading = init_heading - 360;
        }

        double position = imu.get_heading(); //this is where the units are set to be degrees W

        if (position > 180){
            position = position - 360;
        }

        if((rightcorrect < 0) && (position > 0)){
            if((rightcorrect - rightcorrect) >= 180){
                rightcorrect = rightcorrect + 360;
                position = imu.get_heading();
            } 
        } else if ((rightcorrect > 0) && (position < 0)){
            if((rightcorrect - position) >= 180){
            position = imu.get_heading();
            }
        } 

        setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
        int voltageL = calcPID(ltarget, encoderAvgL, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);
        // if(voltageL > 100){ //set left limit
        //     voltageL = 100;
        // } else if (voltageL < -100){
        //     voltageL = -100;
        // }
        int voltageR = calcPID2(rtarget, encoderAvgR, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);
        // if(voltageR > 70){ //set right limit
        //     voltageR = 70;
        // } else if (voltageR < -70){
        //     voltageR = -70;
        // }


        setConstants(ARC_HEADING_KP, ARC_HEADING_KI, ARC_HEADING_KD);
        int fix = calcPID3((init_heading + rightcorrect), position, ARC_HEADING_INTEGRAL_KI, ARC_HEADING_MAX_INTEGRAL, true);

        chasMove((voltageL + fix), (voltageL + fix), (voltageL + fix), (voltageR - fix), (voltageR - fix), (voltageR - fix));
        if ((abs(ltarget - encoderAvgL) <= 4) && (abs(rtarget - encoderAvgR) <= 4)) count++;
        if (count >= 20 || time > timeout){
            break;
        } 

        if (time2 % 50 == 0 && time2 % 100 != 0 && time2 % 150 != 0){
            con.print(0, 0, "ERROR: %f           ", float(error));
        } else if (time2 % 100 == 0 && time2 % 150 != 0){
            con.print(1, 0, "EncoderR: %f           ", float(encoderAvgR));
        } else if (time2 % 150 == 0){
            con.print(2, 0, "Time: %f        ", float(time2));
        } 

        time += 10;
        delay(10);
    }
}



void driveArcRF(double theta, double radius, int timeout){
    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    bool over = false;
    int trueTheta = theta;
    double ltarget = 0;
    double rtarget = 0;
    double ltargetFinal = 0;
    double rtargetFinal = 0;
    double pi =  3.14159265359;
    double init_heading = imu.get_heading();
    // if (init_heading > 180){
    //     init_heading = init_heading - 360;
    // }
    int count = 0;
    int time = 0;
    double rightcorrect = 0;
    resetEncoders();
    con.clear();
    //int timeout = 5000;
    ltargetFinal = double((theta / 360) * 2 * pi * (radius+390)); // * double(2) * pi * double(radius));
    rtargetFinal = double((theta / 360) * 2 * pi * (radius));
    if(theta > 0){
        theta = theta + 45;
    } else{
        theta = theta - 45;
    }
    ltarget = double((theta / 360) * 2 * pi * (radius + 390)); // * double(2) * pi * double(radius));
    rtarget = double((theta / 360) * 2 * pi * (radius));

    while (true){
    
        ColorSort(RingColor);
        if(init_heading > 180){
            init_heading = init_heading - 360;
        }

        double position = imu.get_heading(); //this is where the units are set to be degrees W

        if (position > 180){
            position = position - 360;
        }

        if(((init_heading + rightcorrect) < 0) && (position > 0)){
            if((position - (init_heading + rightcorrect)) >= 180){
                init_heading = init_heading + 360;
                position = imu.get_heading();
            } 
        } else if (((init_heading + rightcorrect)> 0) && (position < 0)){
            if(((init_heading + rightcorrect) - position) >= 180){
            position = imu.get_heading();
            }
        } 

        double encoderAvgL = LF.get_position();
        double encoderAvgR = (RB.get_position() +  RM.get_position()) / 2;
        setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
        int voltageL = calcPID(ltarget, encoderAvgL, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);
        // if(voltageL > 100){ //set left limti
        //     voltageL = 100;
        // } else if (voltageL < -100){
        //     voltageL = -100;
        // }
        int voltageR = calcPID2(rtarget, encoderAvgR, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);
        // if(voltageR > 70){ //set right limit
        //     voltageR = 70;
        // } else if (voltageR < -70){
        //     voltageR = -70;
        // }

        rightcorrect = (encoderAvgR * 360) / (2 * pi * radius);
        setConstants(ARC_HEADING_KP, ARC_HEADING_KI, ARC_HEADING_KD);
        int fix = calcPID3((init_heading + rightcorrect), position, ARC_HEADING_INTEGRAL_KI, ARC_HEADING_MAX_INTEGRAL, true);


    

        chasMove((voltageL + fix), (voltageL + fix), (voltageL + fix), (voltageR - fix), (voltageR - fix), (voltageR - fix));

        // if (theta > 0){
        //     if ((encoderAvgR - rtargetFinal) > 0){
        //         over = true;
        //     }
        // } else {
        //     if ((rtargetFinal - encoderAvgR) > 0){
        //         over = true;
        //     }
        // }

        if(abs((init_heading - position)) > trueTheta){
            over = true;
        }

        if (over || time > timeout){
            break;
        } 

        if (time2 % 50 == 0 && time2 % 100 != 0 && time2 % 150 != 0){
            con.print(0, 0, "ERROR: %f           ", float(error));
        } else if (time2 % 100 == 0 && time2 % 150 != 0){
            con.print(1, 0, "EncoderR: %f           ", float(encoderAvgR));
        } else if (time2 % 150 == 0){
            con.print(2, 0, "Time: %f        ", float(time2));
        } 

        time += 10;
        delay(10);

}
}

