#include "MPU6050.hpp"

int main() {
     MPU6050 mpu;
     std::cout << mpu.testConnection();
     std::cout << mpu.init();
     while(1);
}
