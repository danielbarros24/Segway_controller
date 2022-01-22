#include <Arduino.h>

#include "Accelerometer.h"
#include "Gyroscope.h"

#include "Kalman.h"
#include "Motor.h"

#include "PID.h"


Kalman kalmanX(0.001f, 0.003f, 0.03f); // Create the Kalman instances
Kalman kalmanY(0.001f, 0.003f, 0.03f);

Accelerometer accX(PIN_PA3, 174);
Accelerometer accY(PIN_PA2, 174);

Gyroscope gyroX(PIN_PA4, 15);
Gyroscope gyroY(PIN_PA5, 15);

PID pid(270, 1010, 18, -1, 1);

Motor motorLeft(PIN_PD4, PIN_PD7);
Motor motorRight(PIN_PD5, PIN_PD6);

unsigned long timer;

void setup() {
  Serial.begin(115200);

  analogReference(EXTERNAL);

  accX.setup();
  accY.setup();

  gyroX.setup();
  gyroY.setup();

  pid.setup();

  motorLeft.setup();
  motorRight.setup();

  timer = micros();

  pinMode(PIN_PA6, INPUT);
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

  float steering = max(analogRead(PIN_PA6) / 1023.0 - 0.1, 0);
  
  motorLeft.setDirection(CLOCKWISE);
  motorRight.setDirection(COUNTER_CLOCKWISE);
  
  motorLeft.setSpeed(1 - min(steering, 0.3));
  motorRight.setSpeed(1 - min(steering, 0.3));

  //
  if (output > 0) {
    // motorLeft.setDirection(CLOCKWISE);
    // motorRight.setDirection(CLOCKWISE);

    // steering [0, 1];
    /*float steering = 0.0f;
    
    motorLeft.setSpeed(output * (1 - steering));
    motorRight.setSpeed(output * steering);*/
  } else {
    // motorLeft.setDirection(COUNTER_CLOCKWISE);
    // motorRight.setDirection(COUNTER_CLOCKWISE);

    // set speed
  }

  timer = micros();
}
