#include "pwm.hpp"
#include "servo.hpp"

#include <unistd.h>

int main() {
     /* Zero angle */
     Servo elevationServo = Servo(kPWM1_CHANNEL_0, 180, false);
     elevationServo.setEnabledStatus(true);

     while(1);
}
