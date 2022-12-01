#include "accelerometer.hpp"

int main() {
    Accelerometer acc;
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
    // }
}
