#ifndef _Kalman_h_
#define _Kalman_h_

class Kalman {
public:
    Kalman();

    //Angle in degres, Rate in degrees per second and delta time in seconds
    float getAngle(float newAngle, float newRate, float dt);

    void setAngle(float angle); // Sets the angle
    float getRate(); // Return the unbiased rate

    /* These are used to tune the Kalman filter */
    void setQangle(float Q_angle);
    /*
     * setQbias(float Q_bias)
     * Default value (0.003f) is in Kalman.cpp. 
     * Raise this to follow input more closely,
     * lower this to smooth result of kalman filter.
     */
    void setQbias(float Q_bias);
    void setRmeasure(float R_measure);

    float getQangle();
    float getQbias();
    float getRmeasure();

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