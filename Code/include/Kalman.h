#ifndef _Kalman_h_
#define _Kalman_h_

class Kalman {
public:
    Kalman(float Q_angle, float Q_bias, float R_measure);

    //Angle in degres, Rate in degrees per second and delta time in seconds
    float getAngle(float newAngle, float newRate, float dt);

    void setAngle(float angle); // Sets the angle
    float getRate(); // Return the unbiased rate

private:
    /* Kalman filter variables */
    float Q_angle; // Process noise variance for the accelerometer
    float Q_bias; // Process noise variance for the gyro bias
    float R_measure; // Measurement noise variance

    float angle; // The angle calculated by the Kalman filter
    float bias; // The gyro bias calculated by the Kalman filter
    float rate; // Unbiased rate calculated from the rate and the calculated bias

    float P[2][2]; // Error covariance matrix
};

#endif