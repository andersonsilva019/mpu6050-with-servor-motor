#pragma once

#include <iostream>

#include "pwm.hpp"

class Servo {
private:
    Pwm pwmChannel;
    float currentAngle;
public:
    /* Constructors/Destructor */
    Servo(PwmId pwmOutput, float angle = 0, bool enabledStatus = true);
    ~Servo(void);

    /* Setters */
    void setAngle(float angle);
    void setEnabledStatus(bool enableStatus);

    /* Getters */
    float getAngle(void);
    bool getEnabledStatus(void);
};
