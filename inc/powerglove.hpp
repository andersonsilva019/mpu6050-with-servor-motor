#pragma once

#include "accelerometer.hpp"
#include "gpio.hpp"

class PowerGlove {
private:  
     Accelerometer accelerometerSensor;
     Gpio openClaw;
     Gpio closeClaw;
public:
     PowerGlove(void);
};