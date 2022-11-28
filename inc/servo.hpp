#include <iostream>
#include <string.h>

using std::string;
using std::to_string;

class Servo {
  private:
    float current_angle;
    int duty_cycle;
    int period;
    string pwm_path;
    
  public: 
    Servo(int period, string path);
    ~Servo();
    void init();
    void enable();
    void disable();
    void set_angle(float angle);
    void set_duty_cycle(int duty_cycle);
    void set_period(int period);
    int get_duty_cycle();
    int get_period();
    float get_angle();
};