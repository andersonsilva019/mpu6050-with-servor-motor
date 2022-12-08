#pragma once

#include "servo.hpp"

class RoboticArm {
private:
     Servo rotationServo;
     Servo approximationServo;
     Servo elevationServo;
     Servo grabServo;
public:
     RoboticArm(void);
     RoboticArm(PwmId rotationServo, PwmId elevationServo, PwmId approximationServo, PwmId grabServo);
     void setRotation(float angle);
     void setElevation(float angle);
     void setApproximation(float angle);
     void setGrip(float angle);
     float getRotation(void);
     float getElevation(void);
     float getApproximation(void);
     float getGrip(void);
};