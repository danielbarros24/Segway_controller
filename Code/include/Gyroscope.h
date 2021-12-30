#ifndef _Gyroscope_h_
#define _Gyroscope_h_

#include <stdint.h>

class Gyroscope {
public:
    Gyroscope(uint8_t pin, float sensitivity);

    void setup();

    //Angle in degrees per second
    float getAngleRate();

private:
    uint8_t pin;

    float sensitivity; // Linear sensitivity in mV/(º/s)
};

#endif