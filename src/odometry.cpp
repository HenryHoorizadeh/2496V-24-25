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

double deltaX;
double deltaY;

double startingX;
double startingY;
double startingHeading;

double r0;
double r1;

double delta_left_encoder_pos;
double delta_right_encoder_pos;
double delta_center_encoder_pos;

double prev_left_encoder_pos;
double prev_right_encoder_pos;
double prev_center_encoder_pos;

double left_encoder_pos;
double right_encoder_pos;
double center_encoder_pos;

double localX;
double localY;

double local_polar_angle;
double local_polar_length;
double global_polar_angle;



double phi;

double prev_imu_pos;
double imu_pos;
double imu_pos_radians;

double x_pos;
double y_pos;

double pi = 3.14159265359;

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

void odometry2(){
  prev_imu_pos = imu_pos;
  imu_pos = imu.get_rotation() + startingHeading;
  // if(abs(imu_pos - prev_imu_pos)<IMU_THRESHOLD){
  //   imu_pos = prev_imu_pos;
  // }
  imu_pos_radians = (imu_pos*pi)/180;

        
  prev_left_encoder_pos = left_encoder_pos;
  prev_right_encoder_pos = right_encoder_pos;
  prev_center_encoder_pos = center_encoder_pos;


  left_encoder_pos = (ODOMY.get_position()/36000.0)*(2*pi);
  right_encoder_pos =(ODOMY.get_position()/36000.0)*(2*pi);
  center_encoder_pos = 0;
//((ODOMX.get_position()/36000.0)*(2*pi) )
 // + (imu.get_rotation()/360.0)*(2*pi*4.6)

  delta_left_encoder_pos = left_encoder_pos - prev_left_encoder_pos;
  delta_right_encoder_pos = right_encoder_pos - prev_right_encoder_pos;
  delta_center_encoder_pos = center_encoder_pos - prev_center_encoder_pos;

  // phi = (delta_left_encoder_pos - delta_right_encoder_pos) / trackwidth;

  phi = imu_pos - prev_imu_pos;
  phi = (pi*phi)/180;

  if (phi <= IMU_THRESHOLD) {
    localX = delta_center_encoder_pos;
    localY = delta_right_encoder_pos;
  } else {
    localX = (2*sin(phi/2))*((delta_center_encoder_pos/phi)+FORWARD_OFFSET); 
    localY = (2*sin(phi/2))*((delta_right_encoder_pos/phi)+SIDEWAYS_OFFSET);
  }

  

  if (localX == 0 && localY == 0){
    local_polar_angle = 0;
    local_polar_length = 0;
  } else {
    local_polar_angle = atan2(localY, localX); 
    local_polar_length = sqrt(pow(localX, 2) + pow(localY, 2)); 
  }

  global_polar_angle = local_polar_angle - ((pi*prev_imu_pos)/180) - (phi/2);

  deltaX = local_polar_length*cos(global_polar_angle); 
  deltaY = local_polar_length*sin(global_polar_angle);

  x_pos += deltaX;
  y_pos += deltaY;

  //  if (odo_time % 50 == 0 && odo_time % 100 != 0 && odo_time % 150 != 0){
  //       con.print(0, 0, "x_pos: %f           ", float(x_pos));
  //     } else if (odo_time % 100 == 0 && odo_time % 150 != 0){
  //       con.print(1, 0, "y_pos: %f           ", float(y_pos));
  //     } else if (odo_time % 150 == 0){
  //       con.print(2, 0, "Pos: %f        ", float(center_encoder_pos));
  //     } 

      

  odo_time += 10;


   
}


void driveToPoint (double xTarget, double yTarget, double perferredHeading){

  while(true){
    double turnv = 0;
    odometry2();
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
    odometry2();
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

    setConstants(STRAIGHT_KP*5, STRAIGHT_KI*5, STRAIGHT_KD*5);
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

    chasMove((voltage + heading_correction), (voltage - heading_correction));
    if(abs(hypot) < 1) count++;
    if((count > 20) || (btime > timeout)){
      break;
    }

       if (btime % 50 == 0 && btime % 100 != 0 && btime % 150 != 0){
        con.print(0, 0, "x_pos: %f           ", float(x_pos));
      } else if (btime % 100 == 0 && btime % 150 != 0){
        con.print(1, 0, "y_pos: %f           ", float(y_pos));
      } else if (btime % 150 == 0){
        con.print(2, 0, "Pos: %f        ", float(hypot));
      } 

    


    

  btime += 10;
  delay(10);

  }  

}