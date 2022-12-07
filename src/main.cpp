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

int main(void){
     RoboticArm roboticArm = RoboticArm();
     Accelerometer powerGlove = Accelerometer();
     GPIO gpioOfButton = GPIO(66);

     if (!powerGlove.testConnection())
     {
          std::cerr << "error: Accelerometer connection failed." << std::endl;
          return 0;
     }
     if (!powerGlove.init())
     {
          std::cerr << "error: Accelerometer init failed." << std::endl;
          return 0;
     }

     // Acceleration_t accelerationAxis = {};
     AccelerationRAW_t accelerationAxis = {};

     float angleX = 0;
     float angleY = 0;

     float previousAngleX = 0;
     float previousAngleY = 0;

     while (true)
     {
          /*powerGlove.getAcceleration(&accelerationAxis);

          previousAngleX = angleX;
          previousAngleY = angleY;

          angleX = atan(powerGlove.getAccelerationY()/powerGlove.getAccelerationZ())*RADIAN_TO_DEGREE;
          angleY = atan(powerGlove.getAccelerationX()/powerGlove.getAccelerationZ())*RADIAN_TO_DEGREE;*/

          powerGlove.readAccelRaw(&accelerationAxis);
          std::cout << "X: " << accelerationAxis.x << " Y: " << accelerationAxis.y << " Z: " << accelerationAxis.z << std::endl;
          angleX = map(accelerationAxis.x, -17000, 17000, 0, 180);
          angleY = map(accelerationAxis.y, -17000, 17000, 0, 180);
          float angleZ = map(accelerationAxis.z, -17000, 17000, 0, 180);
          

          // if(angleX > angleY) {
          roboticArm.setElevation(angleX); 

          roboticArm.setRotation(angleY);

          if(gpioOfButton.getValue() == "1") {
               roboticArm.setGrip(180);
          } else {
               roboticArm.setGrip(90);
          }

          // OK
          // angleX = 87
          // previousAngleX = 84

          // OK
          // angleX = 84
          // previousAngleX = 87

          // NOK
          // angleX = 87
          // previousAngleX = -89

          // NOK
          // angleX = -87
          // previousAngleX = 89

          // if((previousAngleX < 89 && angleX > previousAngleX) || (previousAngleX > 1 && angleX > previousAngleX)) {  }

          /*bool superiorSemiCycle = true;

          if((previousAngleX < 0 && angleX > 0) || (previousAngleX > 0 && angleX < 0)) {
               superiorSemiCycle = !superiorSemiCycle;
          }

          if(superiorSemiCycle) {
               roboticArm.setElevation(angleX);
          }

          // float angleZ = atan(powerGlove.getAccelerationY()/powerGlove.getAccelerationX())*RADIAN_TO_DEGREE;

          // roboticArm.setRotation(angleY);

          printf("\033[H\033[J");
          // printf("-> ANGLE Z: %.2f\n", angleZ);
          printf("-> ANGLE X: %.2f\n", angleX);
          printf("-> ANGLE Y: %.2f\n", angleY);*/

          /*
          powerGlove.getAcceleration(&accelerationAxis);

          if(accelerationAxis.x > POWER_GLOVE_MIN_ACCELERATION && accelerationAxis.x > accelerationAxis.y && accelerationAxis.x > accelerationAxis.z) {
               roboticArm.setElevation(accelerationAxis.x/accelerationAxis.z);
               printf("-> X: %.2f\n", accelerationAxis.x);
               printf("-> ELEVATION: %.2f\n", roboticArm.getElevation());
          }

          if(accelerationAxis.y > POWER_GLOVE_MIN_ACCELERATION && accelerationAxis.y > accelerationAxis.x && accelerationAxis.y > accelerationAxis.z) {
               roboticArm.setApproximation(accelerationAxis.y/accelerationAxis.z);
               printf("-> Y: %.2f\n", accelerationAxis.y);
               printf("-> APPROXIMATION: %.2f\n", roboticArm.getApproximation());
          }

          if(accelerationAxis.z > POWER_GLOVE_MIN_ACCELERATION ) {
               roboticArm.setRotation(accelerationAxis.z/accelerationAxis.y);
               printf("-> Z: %.2f\n", accelerationAxis.z);
               printf("-> ROTATION: %.2f\n", roboticArm.getRotation());
          }
          */
          // roboticArm.setRotation(powerGlove.getAccelerationX()/powerGlove.getAccelerationZ());

          // usleep(50'000);
     }

     /* Accelerometer acc;
     if (!acc.testConnection()) {
         std::cout << "Connection failed" << std::endl;
     }

     if (!acc.init()) {
         std::cout << "Init failed" << std::endl;
     }
     std::cout << "Device ID: 0x" << std::hex << (int)acc.getDeviceID() << std::endl;
     std::cout << (int)acc.getFullScaleAccelRange() << std::endl;
     printf("%d\n", acc.getFullScaleAccelRange());

     // Acceleration_t accel;
     // acc.getAcceleration(&accel);
     // std::cout << "Acceleration: " << accel.x << " " << accel.y << " " << accel.z << std::endl;

     std::cout << "Acceleration: X:" << acc.getAccelerationX() << " Y:" << acc.getAccelerationY() << " Z:" << acc.getAccelerationZ() << std::endl;

     // while (1) {
     //     std::cout << "X: " << acc.getAccelerationX() << std::endl;
     //     std::cout << "Y: " << acc.getAccelerationY() << std::endl;
     //     std::cout << "Z: " << acc.getAccelerationZ() << std::endl;
     // } */
}
