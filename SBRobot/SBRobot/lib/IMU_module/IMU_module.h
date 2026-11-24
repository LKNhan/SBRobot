#ifndef IMU_MODULE_H
#define IMU_MODULE_H

#include <Arduino.h>
#include <Wire.h>
#include <math.h>

class IMU_MPU6050{
public: 
    //Nah i don't need constructor
    float accelAngle;
    float gyroRate; 

    float accelX;
    float accelY;
    float accelZ;
    //initialize IMU setting and gyro/accel setting
    void begin();
    void setGyro();
    void setAccel();
    void setAllAccel();
private: 
    void setupIMU();
    void setupGyro();
    void setupAccel();

    float m_accelX_offset = -0.06; //-0.06
    float m_accelZ_offset = -0.09; //-0.09
    float m_accelLSB = 4096.0; //LSB pulled from datasheet
    float m_accelAngle_offset = -0.26;

    float m_gyro_offset = -19;
    float m_gyroLSB = 32.8;
    float m_gyro_offsetGain = 1;
    float m_gyroRate_offset = -0.09;
};

#endif