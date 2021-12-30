#ifndef _PID_h_
#define _PID_h_

#include <stdint.h>

class PID {
public:
    PID(float Kp, float Ki, float Kd, float output_limit_l, float output_limit_h);

    void setup();

    float update(float new_error, float dt);

private:
    float Kp;
    
    float Ki;
    
    float Kd;

    float output_limit_l;

    float output_limit_h;

    //

    float previous_error;

    float previous_integral;
};

#endif