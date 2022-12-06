#pragma once

#include <iostream>

#include "pwm.hpp"

class Servo {
private:
    Pwm pwmChannel;
    float currentAngle;
public:
    Servo(PwmId pwmOutput, float angle = 0, bool enabledStatus = true);
    void setAngle(float angle);
    void setEnabledStatus(bool enableStatus);
    float getAngle(void);
    bool getEnabledStatus(void);
};
