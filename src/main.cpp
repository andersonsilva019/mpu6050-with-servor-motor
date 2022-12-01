#include "accelerometer.hpp"

int main() {
     Accelerometer acc;
     if (!acc.testConnection()) {
          std::cout << "Connection failed" << std::endl;
     }

     if(!acc.init()) {
          std::cout << "Init failed" << std::endl;
     }
     std::cout << "Device ID: 0x" << std::hex << (int)acc.getDeviceID() << std::endl;
     std::cout << (int)acc.getFullScaleAccelRange() << std::endl;
     printf("%d\n", acc.getFullScaleAccelRange());

     // Acceleration_t accValues;
     // while(1) {
     //      acc.getAcceleration(&accValues);
     //      std::cout << "X: " << accValues.x << std::endl;
     //      std::cout << "Y: " << accValues.y << std::endl;
     //      std::cout << "Z: " << accValues.z << std::endl;
     // }
}
