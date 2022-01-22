#include <Arduino.h>
#include "Accelerometer.h"

#include "Config.h"

Accelerometer::Accelerometer(uint8_t pin, float sensitivity)
{
  this->pin = pin;
  this->sensitivity = sensitivity;
}

void Accelerometer::setup() {
  pinMode(this->pin, INPUT);
}

/*

*/

float Accelerometer::getAngle()
{
  int read = analogRead(this->pin);
  int voltage = read * AREF / 1023;
  return asin(voltage / this->sensitivity) * (180 / M_PI);
}