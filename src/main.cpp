#include "accelerometer.hpp"

int main() {
     Accelerometer acc;
     std::cout << acc.testConnection() << std::endl;
     std::cout << acc.init() << std::endl;

     printf("%d", acc.getFullScaleAccelRange());

     Acceleration_t accValues;
     while(1) {
          acc.getAcceleration(&accValues);
          std::cout << "X: " << accValues.x << std::endl;
     }
}
