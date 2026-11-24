#include <Arduino.h>
#include "IMU_module.h"
#include "Motor_module.h"
#include "Control_module.h"
#include "General.h"
#include "SensorFusion_module.h"

float targetAngle = 0 + 1.1;

float motorPWM = 0;
float maxPWM = 20000;

PID pid(500, 0, 0); //Kp, Ki, Kd
IMU_MPU6050 imu;
MOTOR_NEMA17 stepper;
GENERAL general;
COMPLEMENTARY_FILTER fusion(0.98);

void setup() {
  // put your setup code here, to run once:
  general.begin();
  stepper.begin();
  imu.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  imu.setAccel(); //ready accel
  imu.setGyro(); //ready gyro
  general.setTime(); //get dt for sensor fusion / pid
  fusion.setCurrAngle(imu.gyroRate, imu.accelAngle, general.dt); //update the new current angle
  pid.setPID(fusion.currAngle, targetAngle, general.dt); //get pid value

  motorPWM = 1*pid.PID_value;
  if(motorPWM >= maxPWM || motorPWM <= -maxPWM){
    motorPWM = 0;
  }
  stepper.setPWM_frequency(motorPWM);

  // general.serialOut("currentAngle", imu.accelAngle);
}  




