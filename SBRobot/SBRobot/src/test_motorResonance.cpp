#include <Arduino.h>
#include "IMU_module.h"
#include "Motor_module.h"

MOTOR_NEMA17 stepper;
IMU_MPU6050 imu;
int i = 200;
float interval = 500; //1s
float chunk = 0;


void setup(){
    Serial.begin(115200);
    stepper.begin();
    imu.begin();
    chunk += interval;
}

void loop(){   
    if (millis() >= chunk){
        i--;
        chunk += interval;
    }
    imu.setAccel();
    stepper.setPWM_frequency(i);

    Serial.print(">accelAngle:");
    Serial.println(imu.accelAngle);
    Serial.print(">Step per second:");
    Serial.println(i);
}
