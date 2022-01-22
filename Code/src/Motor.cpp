#include <Arduino.h>
#include "Motor.h"

#include "Config.h"

Motor::Motor(uint8_t pinSpeed, uint8_t pinDir)
{
  this->pinSpeed = pinSpeed;
  this->pinDir = pinDir;
}

void Motor::setup() {
  pinMode(this->pinSpeed, OUTPUT);
  pinMode(this->pinDir, OUTPUT);

  this->setDirection(CLOCKWISE);
  this->setSpeed(0.0f);
}

void Motor::setDirection(MotorDirection direction) {
  this->currentDirection = direction;

  if (direction == CLOCKWISE) {
    digitalWrite(this->pinDir, HIGH);
  } else {
    digitalWrite(this->pinDir, LOW);
  }
}

// between 0 and 1
void Motor::setSpeed(float pwm) {
  pwm = constrain(pwm, 0.0f, 1.0f);

  analogWrite(this->pinSpeed, pwm * 255);
}