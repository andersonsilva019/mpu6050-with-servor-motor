#include "../inc/servo.hpp"
#include "../inc/pwm.hpp"

Servo::Servo(int period, string path) {
  this->period = period;
  this->pwm_path = path;
}

Servo::~Servo() {
  this->disable();
}

void Servo::init(){
  // falta o config pin system("config-pin P9.22 pwm");
  set_pwm_duty(to_string(this->duty_cycle).c_str(), strcat((char *) this->pwm_path.c_str(), "/duty_cycle"));
  set_pwm_period(to_string(this->period).c_str(), strcat((char *) this->pwm_path.c_str(), "/period"));
  set_pwm_enable("1", strcat((char *) this->pwm_path.c_str(), "/enable"));
}

void Servo::set_angle(float angle){
  this->current_angle = angle;
  this->duty_cycle = ((angle * 2000000) / 180) + 500000;
  this->set_duty_cycle(this->duty_cycle);
}

void Servo::set_duty_cycle(int duty_cycle){
  this->duty_cycle = duty_cycle;
  set_pwm_duty(to_string(this->duty_cycle).c_str(), strcat((char *) this->pwm_path.c_str(), "/duty_cycle"));
}

void Servo::set_period(int period){
  this->period = period;
  set_pwm_period(to_string(this->period).c_str(), strcat((char *) this->pwm_path.c_str(), "/period"));
}

int Servo::get_duty_cycle(){
  return this->duty_cycle;
}

int Servo::get_period(){
  return this->period;
}

float Servo::get_angle(){
  return this->current_angle;
}

void Servo::enable(){
  set_pwm_enable("1", strcat((char *) this->pwm_path.c_str(), "/enable"));
}

void Servo::disable(){
  set_pwm_enable("0", strcat((char *) this->pwm_path.c_str(), "/enable"));
}