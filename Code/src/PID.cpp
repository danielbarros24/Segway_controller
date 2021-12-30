#include <Arduino.h>
#include "PID.h"

PID::PID(float Kp, float Ki, float Kd, float output_limit_l, float output_limit_h)
{
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
  this->output_limit_l = output_limit_l;
  this->output_limit_h = output_limit_h;

  this->previous_error = 0.0f;
  this->previous_integral = 0.0f;
}

void PID::setup() {
}

/*

*/

float PID::update(float new_error, float dt)
{
  float p = this->Kp * new_error;

  float i = this->previous_integral + this->Ki * (new_error + this->previous_error) * dt * 0.5f;
  i = constrain(i, this->output_limit_l, this->output_limit_h);
  this->previous_integral = i;

  float d = this->Kd * (new_error - this->previous_error) / dt;

  float output = p + i + d;
  output = constrain(output, this->output_limit_l, this->output_limit_h);
  this->previous_error = new_error;

  return output;
}