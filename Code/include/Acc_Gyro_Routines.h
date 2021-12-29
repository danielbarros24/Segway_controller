#include <Arduino.h>

#define ACC_SENSIVITY 312
#define GYRO_SENSIVITY 2
#define M_PI 3.14159265358979323846


void calibrateSensors();
void init_pins();
double getAccXAngle();
double getAccYAngle();
double getGyroXRate();
double getGyroYRate();
