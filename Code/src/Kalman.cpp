#include "Kalman.h"

Kalman::Kalman(float Q_angle, float Q_bias, float R_measure)
{
    Q_angle = Q_angle;
    Q_bias = Q_bias;
    R_measure = R_measure;

    //Reset values
    angle = 0.0f;
    bias = 0.0f;

    //The error covariance matrix as well
    P[0][0] = 0.0f;
    P[0][1] = 0.0f;
    P[1][0] = 0.0f;
    P[1][1] = 0.0f;
};

/*

*/

//Angle in degres, Rate in degrees per second and delta time in seconds
float Kalman::getAngle(float newAngle, float newRate, float dt)
{
    /* Step 1 */
    rate = newRate - bias;
    angle += dt * rate;

    // Update estimation error covariance - Project the error covariance ahead
    /* Step 2 */
    P[0][0] += dt * (dt * P[1][1] - P[0][1] - P[1][0] + Q_angle);
    P[0][1] -= dt * P[1][1];
    P[1][0] -= dt * P[1][1];
    P[1][1] += Q_bias * dt;

    // Calculate Kalman gain - Compute the Kalman gain
    /* Step 4 */
    float S = P[0][0] + R_measure; // Estimate error

    /* Step 5 */
    float K[2]; // Kalman gain - This is a 2x1 vector
    K[0] = P[0][0] / S;
    K[1] = P[1][0] / S;

    // Calculate angle and bias - Update estimate with measurement zk (newAngle)
    /* Step 3 */
    float y = newAngle - angle; // Angle difference

    /* Step 6 */
    angle += K[0] * y;
    bias += K[1] * y;

    // Calculate estimation error covariance - Update the error covariance
    /* Step 7 */
    float P00_temp = P[0][0];
    float P01_temp = P[0][1];

    P[0][0] -= K[0] * P00_temp;
    P[0][1] -= K[0] * P01_temp;
    P[1][0] -= K[1] * P00_temp;
    P[1][1] -= K[1] * P01_temp;

    return angle;
};

/*

*/

void Kalman::setAngle(float angle)
{
    // Used to set angle, this should be set as the starting angle
    this->angle = angle;
};

float Kalman::getRate()
{
    // Return the unbiased rate
    return this->rate;
};