#include "servo.hpp"

#include "common.hpp"

#define SERVO_PERIOD_NS                 20'000'000
#define SERVO_MINIMUM_DEGREE            0
#define SERVO_MAXIMUM_DEGREE            180
#define SERVO_DUTY_CYCLE_MIN_DEGREE     500'000
#define SERVO_DUTY_CYCLE_MAX_DEGREE     2'500'000

Servo::Servo(PwmId pwmOutput, float angle, bool enabledStatus) : pwmChannel(pwmOutput) {
    this->pwmChannel.setPeriod(SERVO_PERIOD_NS);
    this->setAngle(angle);
    this->pwmChannel.setEnabledStatus(enabledStatus);
}

/* Setters */
void Servo::setAngle(float angle) {
    if (angle > SERVO_MAXIMUM_DEGREE || angle < SERVO_MINIMUM_DEGREE) {
        return;
    }
    this->currentAngle = angle;
    long servoDutyCycle = map(angle, SERVO_MINIMUM_DEGREE, SERVO_MAXIMUM_DEGREE, SERVO_DUTY_CYCLE_MIN_DEGREE, SERVO_DUTY_CYCLE_MAX_DEGREE);
    this->pwmChannel.setDutyCycle(servoDutyCycle);
}

void Servo::setEnabledStatus(bool enableStatus) {
    this->pwmChannel.setEnabledStatus(enableStatus);
}


/* Getters */
float Servo::getAngle(void) {
    return this->currentAngle;
}

bool Servo::getEnabledStatus(void) {
    return this->pwmChannel.getEnabledStatus();
}
