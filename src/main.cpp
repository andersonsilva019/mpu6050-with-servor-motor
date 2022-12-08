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
     Accelerometer powerGlove = Accelerometer();
     GPIO gpioOfButton = GPIO(66); //P8_7
     gpioOfButton.setEdge("rising");

     if (!powerGlove.testConnection()) {
          std::cerr << "error: Accelerometer connection failed." << std::endl;
          return 0;
     }
     if (!powerGlove.init()) {
          std::cerr << "error: Accelerometer init failed." << std::endl;
          return 0;
     }

     // Acceleration_t accelerationAxis = {};
     AccelerationRAW_t accelerationAxis = {};

     float angleX = 0;
     float angleY = 0;

     float previousAngleX = 0;
     float previousAngleY = 0;

     while (true) {

          powerGlove.readAccelRaw(&accelerationAxis);
          //std::cout << "X: " << accelerationAxis.x << " Y: " << accelerationAxis.y << std::endl;
          angleX = map(accelerationAxis.x, -17000, 17000, 180, 0);
          angleY = map(accelerationAxis.y, -17000, 17000, 0, 180);

          roboticArm.setElevation(angleX);

          roboticArm.setRotation(angleY);

          if (gpioOfButton.getValue()) {
               roboticArm.setGrip(180);
          }
          else {
               roboticArm.setGrip(120);
          }
     }

     /* 
     std::cout << "Device ID: 0x" << std::hex << (int)acc.getDeviceID() << std::endl;
     std::cout << (int)acc.getFullScaleAccelRange() << std::endl;
     printf("%d\n", acc.getFullScaleAccelRange());
     */
     
}
