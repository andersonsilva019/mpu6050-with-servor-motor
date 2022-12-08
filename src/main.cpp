#include "accelerometer.hpp"
#include "roboticarm.hpp"
#include "common.hpp"
#include "gpio.hpp"

#include <iostream>
#include <cmath>

#include <unistd.h>

#define POWER_GLOVE_MIN_ACCELERATION 0.5
#define PI 3.14159265359
#define RADIAN_TO_DEGREE 57.2958

int main(void) {
     RoboticArm roboticArm = RoboticArm();
     Accelerometer controlSensor = Accelerometer();
     GPIO touchSensor = GPIO(66); //P8_7
     GPIO startLed = GPIO(67); //P8_8
     GPIO touchLed = GPIO(68); //P8_10

     touchSensor.setDirection("in");
     touchSensor.setEdge("rising");

     startLed.setDirection("out");
     touchLed.setDirection("out");

     if (!controlSensor.testConnection()) {
          std::cerr << "error: Accelerometer connection failed." << std::endl;
          return 0;
     }
     if (!controlSensor.init()) {
          std::cerr << "error: Accelerometer init failed." << std::endl;
          return 0;
     }

     // Acceleration_t accelerationAxis = {};
     AccelerationRAW_t accelerationAxis = {};

     float angleX = 0;
     float angleY = 0;

     float previousAngleX = 0;
     float previousAngleY = 0;
     startLed.setValue(1);

     while (true) {
          controlSensor.readAccelRaw(&accelerationAxis);
          // std::cout << "X: " << accelerationAxis.x << " Y: " << accelerationAxis.y << std::endl;
          angleX = map(accelerationAxis.y, -17000, 17000, 180, 0);
          angleY = map(accelerationAxis.x, -17000, 17000, 0, 180);

          roboticArm.setApproximation(angleX);
          roboticArm.setRotation(angleY);

          if (touchSensor.getValue()) {
               touchLed.setValue(1);
               roboticArm.setGrip(180);
          }
          else {
               touchLed.setValue(0);
               roboticArm.setGrip(120);
          }
     }

     /* 
     std::cout << "Device ID: 0x" << std::hex << (int)acc.getDeviceID() << std::endl;
     std::cout << (int)acc.getFullScaleAccelRange() << std::endl;
     printf("%d\n", acc.getFullScaleAccelRange());
     */
     
}
