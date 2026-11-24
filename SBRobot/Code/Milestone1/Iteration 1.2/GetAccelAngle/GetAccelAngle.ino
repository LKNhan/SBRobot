#include <Wire.h>
#include "math.h"

//get gyro angle around y axis
float accelX_offset = -3494, accelY_offset = -1609, accelZ_offset = 949;
float accelX, accelY, accelZ;
float accelLSB = 4096.0;
float accel_offsetGain = 0;
float accelAngle = 0;

float dt = 0, current_time, previous_time;

void setupAccel(){
  Wire.setClock(400000); //max clock speed of 400KHZ
  Wire.begin();

  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00); //set to power mode, all sleep function disable
  Wire.endTransmission();

  //Set i2c to adress of gyro
  Wire.beginTransmission(0x68);
  //Low pass for gyro 
  Wire.write(0x1A);
  Wire.write(0x05);
  Wire.endTransmission();

  //Change sensitivity to 65.5 LSB
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x16);
  Wire.endTransmission();
}
void getAccel(){
  Wire.beginTransmission(0x68);
  Wire.write(0x3B); //just access the accel register
  Wire.endTransmission();

  Wire.requestFrom(0x68, 6); //pull 2 byte for gyroY
  int16_t accelX_LSB = Wire.read() << 8 | Wire.read(); //signed 16 bit integer
  int16_t accelY_LSB = Wire.read() << 8 | Wire.read(); //signed 16 bit integer
  int16_t accelZ_LSB = Wire.read() << 8 | Wire.read(); //signed 16 bit integer
  // accelX_LSB += accelX_offset*accel_offsetGain;
  // accelY_LSB += accelY_offset*accel_offsetGain;
  // accelZ_LSB += accelZ_offset*accel_offsetGain;

  accelX = (float) accelX_LSB/accelLSB - 0.06;
  accelY = (float) accelY_LSB/accelLSB + 0.03;
  accelZ = (float) accelZ_LSB/accelLSB - 0.09;

  accelAngle = atan2(accelX, accelZ)*RAD_TO_DEG;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(250);

  setupAccel();

}

void loop() {
  // put your main code here, to run repeatedly:
  getAccel(); //update gyro rate global value

  Serial.print("AccelX");
  Serial.print(accelX);
  Serial.print(", ");
  Serial.print("AccelY");
  Serial.print(accelY);
  Serial.print(", ");
  Serial.print("AccelZ");
  Serial.print(accelZ);
  Serial.print(", ");
  Serial.print("accelAngle:");
  Serial.print(accelAngle);
  Serial.println();

}
