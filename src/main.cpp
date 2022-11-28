#include "pwm.hpp"
#include "servo.hpp"

int main() {
     /* One-by-one */
     Pwm pwm01_0 = Pwm(kPWM1_CHANNEL_0);
     pwm01_0.setPeriod(20'000'000);
     pwm01_0.setDutyCycle(500'000);
     pwm01_0.setEnabledStatus(true);

     /* All-at-once */
     Pwm pwm01_1 = Pwm(kPWM1_CHANNEL_1, 20'000'000, 2'500'000);

     /* Zero angle */
     Servo rotationServo = Servo(kPWM3_CHANNEL_0);
     Servo elevationServo = Servo(kPWM3_CHANNEL_1, 0, false);
     elevationServo.setEnabledStatus(true);

     /* Other's angles */
     Servo lungeServo = Servo(kPWM6_CHANNEL_0, 90);
     Servo clawServo = Servo(kPWM6_CHANNEL_1, 180);
}
