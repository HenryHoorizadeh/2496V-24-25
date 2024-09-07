#include "api.h"
#include "main.h"
#include "pid.h"
#include "robot.h"
#include "auton.h"
#include "odometry.h"

using namespace pros;
using namespace std;

int turnv = 0;

double absoluteAngleToTarget = 0;
double position = 0;

float deltaX;
float deltaY;

float startingX;
float startingY;
float startingHeading;

float r0;
float r1;

float delta_left_encoder_pos;
float delta_right_encoder_pos;
float delta_center_encoder_pos;

float prev_left_encoder_pos;
float prev_right_encoder_pos;
float prev_center_encoder_pos;

float left_encoder_pos;
float right_encoder_pos;
float center_encoder_pos;

float localX;
float localY;

float phi;

float prev_imu_pos;
float imu_pos;

float x_pos;
float y_pos;

float pi = 3.14159265359;

int odo_time = 0;

void setPosition(float xcoord, float ycoord, float heading){
    startingX = xcoord;
    startingY = ycoord;
    
    startingHeading = heading;
  
    x_pos = startingX;
    y_pos = startingY;
}
  
void odometry (){


        prev_imu_pos = imu_pos;
        imu_pos = imu.get_rotation() + startingHeading;
        
        prev_left_encoder_pos = left_encoder_pos;
        prev_right_encoder_pos = right_encoder_pos;
        prev_center_encoder_pos = center_encoder_pos;

        left_encoder_pos = LF.get_position();
        right_encoder_pos = RF.get_position();
        center_encoder_pos = 0;

        delta_left_encoder_pos = left_encoder_pos - prev_left_encoder_pos;
        delta_right_encoder_pos = right_encoder_pos - prev_right_encoder_pos;
        delta_center_encoder_pos = center_encoder_pos - prev_center_encoder_pos;

        // phi = (delta_left_encoder_pos - delta_right_encoder_pos) / trackwidth;

        phi = imu_pos - prev_imu_pos;

        r0 = ((delta_left_encoder_pos + delta_right_encoder_pos) / 2) / phi;
        r1 = delta_center_encoder_pos/phi;

        if (phi < IMU_THRESHOLD){
        localX = (delta_left_encoder_pos + delta_right_encoder_pos) / 2;
        localY = delta_center_encoder_pos - FORWARD_OFFSET * ((pi*phi)/180);
        } else {
        localX = r0*sin((pi*phi)/180) - r1*(1-cos((pi*phi)/180));
        localY= r1*sin((pi*phi)/180) + r0*(1-cos((pi*phi)/180));
        }





        deltaY = localX * cos((pi * imu_pos)/180) - localY * sin((pi * imu_pos)/180);
        deltaX = localX * sin((pi * imu_pos)/180) + localY * cos((pi * imu_pos)/180);

        x_pos += deltaX;
        y_pos += deltaY;

      if (odo_time % 50 == 0 && odo_time % 100 != 0 && odo_time % 150 != 0){
        con.print(0, 0, "x_pos: %f           ", float(x_pos));
      } else if (odo_time % 100 == 0 && odo_time % 150 != 0){
        con.print(1, 0, "y_pos: %f           ", float(y_pos));
      } else if (odo_time % 150 == 0){
        con.print(2, 0, "Pos: %f        ", float(position));
      } 

      

        odo_time += 10;

}

void driveToPoint (double xTarget, double yTarget, double perferredHeading){

  while(true){
    double turnv = 0;
    odometry();
      double distanceToTarget = sqrt(pow((x_pos - xTarget),2) + pow((y_pos - yTarget),2));
      double absoluteAngleToTarget = atan2(pow((x_pos - xTarget),2), pow((y_pos - yTarget),2));

      double angleToTarget = absoluteAngleToTarget - (imu_pos - 90);

      while (angleToTarget >= 360) {
        angleToTarget = angleToTarget - 360;
      }

      while (angleToTarget <= -360){
        angleToTarget = angleToTarget + 360;
      }

      double relativeXToPoint = cos((pi*angleToTarget)/180) * distanceToTarget;
      double relativeYToPoint = sin((pi*angleToTarget)/180) * distanceToTarget;
      double relativeTurnAngle = angleToTarget - 180 + perferredHeading;

      double movementXPower = relativeXToPoint / (abs(relativeXToPoint) + abs(relativeYToPoint));
      double movementYPower = relativeYToPoint / (abs(relativeXToPoint) + abs(relativeYToPoint));
      
      //double movementTurn = clamp(((angleToTarget)/30), 1, -1);
      //I havent finished this yet 




  }


}



void boomerang(double xTarget, double yTarget){
  double hypot = 0;
  double voltage = 0;
  double heading_correction = 0;
  int btime = 0;
  int timeout = 30000;
  int count = 0;


  while(true){
    odometry();
    hypot = sqrt(pow((x_pos - xTarget),2) + pow((y_pos - yTarget),2));
    absoluteAngleToTarget = atan2((xTarget - x_pos),(yTarget - y_pos)) * (180/pi);

    if (absoluteAngleToTarget > 180){
      absoluteAngleToTarget = absoluteAngleToTarget - 360;
    }

    position = imu.get_heading(); //this is where the units are set to be degrees

    if (position > 180){
            position = position - 360;
    }

    if((absoluteAngleToTarget < 0) && (position > 0)){
        if((position - absoluteAngleToTarget) >= 180){
            absoluteAngleToTarget = absoluteAngleToTarget + 360;
            position = imu.get_heading();
            turnv = (absoluteAngleToTarget - position); // target + position
        } else {
             turnv = (abs(position) + abs(absoluteAngleToTarget));
        }
    } else if ((absoluteAngleToTarget > 0) && (position < 0)){

        if((absoluteAngleToTarget - position) >= 180){
           position = imu.get_heading();
            turnv = abs(abs(position) - abs(absoluteAngleToTarget));
        } else {
            turnv = (abs(position) + absoluteAngleToTarget);
        }

    } else {
         turnv = abs(abs(position) - abs(absoluteAngleToTarget));
    }


        if(abs(turnv) > 90){
          absoluteAngleToTarget = absoluteAngleToTarget + 180;
          hypot = -hypot;
        }
        if (absoluteAngleToTarget >= 359){
            absoluteAngleToTarget = absoluteAngleToTarget - 360;
        }

        if((absoluteAngleToTarget < 0) && (position > 0)){
            if((position - absoluteAngleToTarget) >= 180){
                absoluteAngleToTarget = absoluteAngleToTarget + 360;
                position = imu.get_heading();
            } 
        } else if ((absoluteAngleToTarget > 0) && (position < 0)){
            if((absoluteAngleToTarget - position) >= 180){
            position = imu.get_heading();
            }
        } 
    setConstants(TURN_KP, TURN_KI, TURN_KD);
    heading_correction = calcPID(absoluteAngleToTarget, position, TURN_INTEGRAL_KI, TURN_MAX_INTEGRAL, true);

    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    // if(abs(position - absoluteAngleToTarget) < 90){
    //   voltage = -calcPID2(0, hypot, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);
    // } else {
    //   voltage = calcPID2(0, hypot, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);
    // }
    voltage = -calcPID2(0, hypot, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL, true);

    if(voltage > 127){
      voltage = 127;
    } else if(voltage < -127) {
      voltage = -127;
    }

    if(abs(hypot) < HEADING_CUTOFF){
      heading_correction = 0;
    }

    chasMove((voltage + heading_correction), (voltage + heading_correction), (voltage + heading_correction), (voltage - heading_correction), (voltage - heading_correction), (voltage - heading_correction));
    if(abs(hypot) < 15) count++;
    if((count > 20) || (btime > timeout)){
     // break;
    }

    


    

  btime += 10;
  delay(10);

  }  

}