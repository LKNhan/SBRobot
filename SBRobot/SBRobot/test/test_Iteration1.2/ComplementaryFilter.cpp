#include "Arduino.h"
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "math.h"

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;

int16_t accX, accZ;
float accAngle;

int16_t gyroY, gyroRate;
float gyroAngle=0;
float currentAngle=0;
float currentAngle_offset = 3.18;
unsigned long currTime, prevTime, loopTime;
float alpha = 0.98;

void setup() {  
  mpu.initialize();
  Serial.begin(115200);

  prevTime = micros();
}

void loop() {  
  currTime = micros();
  loopTime = currTime - prevTime;
  prevTime = currTime;
  

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  accX = ax;
  accZ = az;
  gyroY = gy;


  gyroRate = gyroY/131.0;  

  accAngle = atan2(accX, accZ)*RAD_TO_DEG;

  currentAngle = alpha*(currentAngle + (float)gyroRate*loopTime/1000000.0) + (1-alpha) * (accAngle);
  

  Serial.print("accAngle:");
  Serial.print(accAngle);
  Serial.print(", ");
  Serial.print("currentAngle:");
  Serial.print(currentAngle-currentAngle_offset);
  Serial.println();




}