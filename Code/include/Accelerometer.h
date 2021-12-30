#ifndef _Accelerometer_h_
#define _Accelerometer_h_

#include <stdint.h>

class Accelerometer {
public:
    Accelerometer(uint8_t pin, float sensitivity);

    void setup();

    //Angle in degrees
    float getAngle();

private:
    uint8_t pin;

    float sensitivity; // Linear sensitivity in mV/g
};

#endif