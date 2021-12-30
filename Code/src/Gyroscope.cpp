#include <Arduino.h>
#include "Gyroscope.h"

Gyroscope::Gyroscope(uint8_t pin, float sensitivity)
{
  this->pin = pin;
  this->sensitivity = sensitivity;
}

void Gyroscope::setup() {
  pinMode(this->pin, INPUT);
}

/*

*/

float Gyroscope::getAngleRate()
{
  int read = analogRead(this->pin);
  int voltage = read * 5000 / 1023;
  return voltage / this->sensitivity;
}