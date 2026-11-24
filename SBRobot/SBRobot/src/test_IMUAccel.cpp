/*
Gather IMU data, check for a way of removing the spike before turning

*/

#include <Arduino.h>
#include "IMU_module.h"
#include "Motor_module.h"
#include "General.h"

GENERAL general;
IMU_MPU6050 imu;

float gyroAngle = 0;
double currAngle = 0;
float a = 0.98;

void setup(){
    general.begin();
    imu.begin();
}

void loop(){   
    // imu.setAccel();
    imu.setGyro();
    imu.setAccel();
    general.setTime();
    gyroAngle += imu.gyroRate*general.dt;
    currAngle = a*(currAngle + imu.gyroRate*general.dt) + (1-a)*(imu.accelAngle); //sensor fusion

    general.serialOut("gyroAngle", gyroAngle);
    general.serialOut("accelAngle", imu.accelAngle); 
    general.serialOut("currntAngle", currAngle);
    
}

