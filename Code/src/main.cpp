#include <Arduino.h>
#include "Kalman.h"


/* Acc & Gyro constants */
const int groundpin = 18;             // analog input pin 4 -- ground
const int powerpin = 19;              // analog input pin 5 -- voltage

const int acc_xpin = A4;              // x-axis accelerometer output
const int acc_ypin = A3;              // y-axis accelerometer output

const int gyro_xpin = A2;             // x-axis gyroscope output
const int gyro_ypin = A1;             // y-axis gyroscope output

int acc_x = 0;                        //Variable to store xpin value
int acc_y = 0;                        //Variable to store ypin value

int gyro_x = 0;                       //Variable to store xpin value
int gyro_y = 0;                       //Variable to store ypin value


void setup() {

  Serial.begin(9600);
  /* Code section related to Gyro & Acc and Kalman filter */

  /* Acc & Gyro*/
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);

  digitalWrite(groundpin, LOW);
  digitalWrite(powerpin, HIGH);

}

void loop() {

  /* Code section related to Gyro & Acc and Kalman filter */

  /* Acc */
  acc_x = analogRead(acc_xpin);
  acc_y = analogRead(acc_ypin);

  /* Gyro */
  gyro_x = analogRead(gyro_xpin);
  gyro_y = analogRead(gyro_ypin);

}