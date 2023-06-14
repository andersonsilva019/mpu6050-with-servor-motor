// Copyright (c) 2023 Robarm
// All rights reserved

#include "module/roboticarm/include/roboticarm.hpp"

robarm::module::roboticarm::RoboticArm::RoboticArm(hal::pwm::PWM_ChannelId rotation_servo_channel, hal::pwm::PWM_ChannelId elevation_servo_channel, hal::pwm::PWM_ChannelId approximation_servo_channel, hal::pwm::PWM_ChannelId grab_servo_channel) : 
     rotation_servo_(rotation_servo_channel, 90.0),
     approximation_servo_(approximation_servo_channel), 
     elevation_servo_(elevation_servo_channel), 
     grab_servo_(grab_servo_channel, 120.0) { }
