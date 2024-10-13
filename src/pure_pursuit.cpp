# include "pure_pursuit.h"
#include "main.h"
#include "api.h"
#include "auton.h"
#include "pid.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "robot.h"
#include "odometry.h"
#include "main.h"
#include <vector>
#include <cmath>

using namespace std;
using namespace pros;

// Define a struct for points
struct Point {
    double x;
    double y;
};

// Define a struct for intersections
struct Intersection {
    Point point;
    size_t segmentIndex;
    double t;
};

// Global variables
vector<Point> path;
vector<double> pathDistances;
double lookaheadDistance = 500.0; // Adjust as needed (in mm)
double robotVelocity = 35.0;     // Desired robot velocity (in voltage)
double wheelbase = 230.0;         // Distance between left and right wheels (in encoder_units)



// Function to initialize the path
void initializePath() {
    // Define your path here
    path.clear();
    path.push_back({0, 0});
    //path.push_back({0, 500});
    path.push_back({500, 500});
    path.push_back({1000, 1000});
    path.push_back({0, 1000});
    path.push_back({0, 0});


    //path.push_back({2000, 500});
    // Add more points as needed
}

// Function to precompute distances along the path
void initializePathDistances() {
    pathDistances.clear();
    pathDistances.push_back(0);
    for (size_t i = 1; i < path.size(); i++) {
        double dx = path[i].x - path[i - 1].x;
        double dy = path[i].y - path[i - 1].y;
        double dist = sqrt(dx * dx + dy * dy);
        pathDistances.push_back(pathDistances.back() + dist);
    }
}



// Function to compute circle-line intersections
vector<Intersection> getCircleLineIntersections(double r, Point center, Point p1, Point p2, size_t segmentIndex) {
    vector<Intersection> result;

    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;

    double fx = p1.x - center.x;
    double fy = p1.y - center.y;

    double a = dx * dx + dy * dy;
    double b = 2 * (fx * dx + fy * dy);
    double c = fx * fx + fy * fy - r * r;

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return result; // No intersection
    }

    discriminant = sqrt(discriminant);

    double t1 = (-b - discriminant) / (2 * a);
    double t2 = (-b + discriminant) / (2 * a);

    if (t1 >= 0 && t1 <= 1) {
        Point intersection;
        intersection.x = p1.x + t1 * dx;
        intersection.y = p1.y + t1 * dy;
        result.push_back({intersection, segmentIndex, t1});
    }

    if (t2 >= 0 && t2 <= 1) {
        Point intersection;
        intersection.x = p1.x + t2 * dx;
        intersection.y = p1.y + t2 * dy;
        result.push_back({intersection, segmentIndex, t2});
    }

    return result;
}

// Function to find the goal point
Point findGoalPoint(Point robotPosition, double lookaheadDistance) {
    vector<Intersection> intersections;

    // Find all intersections between the lookahead circle and path segments
    for (size_t i = 0; i < path.size() - 1; i++) {
        Point start = path[i];
        Point end = path[i + 1];

        vector<Intersection> points = getCircleLineIntersections(
            lookaheadDistance, robotPosition, start, end, i);

        intersections.insert(intersections.end(), points.begin(), points.end());
    }

    // Select the intersection point that is the furthest along the path
    double maxProgress = -1;
    Intersection bestIntersection;

    for (const auto& inter : intersections) {
        double segmentStartDistance = pathDistances[inter.segmentIndex];
        double segmentLength = pathDistances[inter.segmentIndex + 1] - segmentStartDistance;
        double progress = segmentStartDistance + inter.t * segmentLength;

        if (progress > maxProgress) {
            maxProgress = progress;
            bestIntersection = inter;
        }
    }

    if (maxProgress >= 0) {
        return bestIntersection.point;
    } else {
        // No valid intersection found; return the last point in the path
        return path.back();
    }
}

// Function to compute the curvature
double computeCurvature(Point robotPosition, double robotHeading, Point goalPoint, double lookaheadDistance) {
    double dx = goalPoint.x - robotPosition.x;
    double dy = goalPoint.y - robotPosition.y;

    // Transform the goal point to the robot's coordinate frame
    double x = cos(robotHeading) * dx + sin(robotHeading) * dy;
    double y = -sin(robotHeading) * dx + cos(robotHeading) * dy;

    // Avoid division by zero
    if (fabs(x) < 1e-6) {
        return 0.0;
    }

    double curvature = (2.0 * x) / (lookaheadDistance * lookaheadDistance);

    return curvature;
}

// Function to compute wheel speeds based on curvature
void computeWheelSpeeds(double curvature, double& leftSpeed, double& rightSpeed) {
    leftSpeed = robotVelocity * (1.0 - (curvature * wheelbase / 2.0));
    rightSpeed = robotVelocity * (1.0 + (curvature * wheelbase / 2.0));
}

// Function to set motor speeds
void setMotorSpeeds(double leftSpeed, double rightSpeed) {
// Convert speeds from mm/s to motor RPM if necessary
    // Assuming 200 RPM motors and wheel circumference of 320 mm (for 4" wheels)
    // double wheelCircumference = 4.0 * 25.4 * M_PI; // 4-inch wheels
    // double maxRPM = 600.0;

    // double leftRPM = (leftSpeed / wheelCircumference) * 60.0;
    // double rightRPM = (rightSpeed / wheelCircumference) * 60.0;

    // // Clamp RPM values to max motor RPM
    // leftRPM = std::max(std::min(leftRPM, maxRPM), -maxRPM);
    // rightRPM = std::max(std::min(rightRPM, maxRPM), -maxRPM);

    // // Set motor velocities
    // LF.move_velocity(leftRPM);
    // LM.move_velocity(leftRPM);
    // LB.move_velocity(leftRPM);
    // RF.move_velocity(rightRPM);
    // RM.move_velocity(rightRPM);
    // RB.move_velocity(rightRPM);

    LF.move(leftSpeed);
    LM.move(leftSpeed);
    LB.move(leftSpeed);
    RF.move(rightSpeed);
    RM.move(rightSpeed);
    RB.move(rightSpeed);


}

// The main Pure Pursuit controller loop
void purePursuitController() {
    while (true) {
        odometry2();
        // Get robot's current position and heading
        double robotX = x_pos;
        double robotY = y_pos;
        double robotHeading = imu_pos_radians; // In radians

        Point robotPosition = {robotX, robotY};

        // Find the goal point
        Point goalPoint = findGoalPoint(robotPosition, lookaheadDistance);

        // Compute the curvature
        double curvature = computeCurvature(robotPosition, robotHeading, goalPoint, lookaheadDistance);

        // Compute wheel speeds
        double leftSpeed, rightSpeed;
        computeWheelSpeeds(curvature, leftSpeed, rightSpeed);

    
        setMotorSpeeds(leftSpeed, rightSpeed);

        delay(10);
    }
}


//add motion tracking





