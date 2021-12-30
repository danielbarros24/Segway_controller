#include <Arduino.h>

#include "Accelerometer.h"
#include "Gyroscope.h"

#include "Kalman.h"

#include "PID.h"


Kalman kalmanX(0.001f, 0.003f, 0.03f); // Create the Kalman instances
Kalman kalmanY(0.001f, 0.003f, 0.03f);

Accelerometer accX(A5, 312);
Accelerometer accY(A4, 312);

Gyroscope gyroX(A3, 2);
Gyroscope gyroY(A2, 2);

PID pid(100, 100, 100, -1, 1);

unsigned long timer;

void setup() {
  Serial.begin(115200);

  accX.setup();
  accY.setup();

  gyroX.setup();
  gyroY.setup();

  pid.setup();

  timer = micros();
}

void loop() {
  float dt = (micros() - timer) / 1000000.0f;

  /* Get Acc & Gyro values */
  float pitch = accX.getAngle();
  float roll = accY.getAngle();

  float rate_x = gyroX.getAngleRate();
  float rate_y = gyroY.getAngleRate();

  /* Extract angles from kalman filter */
  float kalAngleX = kalmanX.getAngle(pitch, rate_x, dt);
  float kalAngleY = kalmanY.getAngle(roll, rate_y, dt);

  float error = 0 - kalAngleY;
  float output = pid.update(error, dt);

  timer = micros();
}
