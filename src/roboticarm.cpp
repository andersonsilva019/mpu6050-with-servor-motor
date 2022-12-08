#include "roboticarm.hpp"

RoboticArm::RoboticArm(void) :
     rotationServo(kPWM1_CHANNEL_0, 90.0),
     approximationServo(kPWM1_CHANNEL_1),
     elevationServo(kPWM4_CHANNEL_0),
     grabServo(kPWM4_CHANNEL_1, 120.0) { }

RoboticArm::RoboticArm(PwmId rotationServo, PwmId elevationServo, PwmId approximationServo, PwmId grabServo) : 
     rotationServo(rotationServo, 90.0),
     approximationServo(approximationServo), 
     elevationServo(elevationServo), 
     grabServo(grabServo, 120.0) { }

void RoboticArm::setRotation(float angle) {
     this->rotationServo.setAngle(angle);
}

void RoboticArm::setElevation(float angle) {
     this->elevationServo.setAngle(angle);
}

void RoboticArm::setApproximation(float angle) {
     this->approximationServo.setAngle(angle);
}

void RoboticArm::setGrip(float angle) {
     this->grabServo.setAngle(angle);
}

float RoboticArm::getRotation(void) {
     return this->rotationServo.getAngle();
}

float RoboticArm::getElevation(void) {
     return this->elevationServo.getAngle();
}

float RoboticArm::getApproximation(void) {
     return this->approximationServo.getAngle();
}

float RoboticArm::getGrip(void) {
     return this->grabServo.getAngle();
}
