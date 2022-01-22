#ifndef _Motor_h_
#define _Motor_h_

#include <stdint.h>

enum MotorDirection {
    CLOCKWISE,
    COUNTER_CLOCKWISE
};

class Motor {
public:
    Motor(uint8_t pinSpeed, uint8_t pinDir);

    void setup();

    void setDirection(MotorDirection direction);

    // between 0 and 1
    void setSpeed(float pwm);

private:
    uint8_t pinSpeed;
    uint8_t pinDir;

    float currentPWM;
    MotorDirection currentDirection;
};

#endif