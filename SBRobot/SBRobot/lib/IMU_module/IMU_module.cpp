#include "IMU_module.h"


void IMU_MPU6050::begin(){
    setupIMU();
    setupGyro();
    setupAccel();
}
void IMU_MPU6050::setupIMU(){
  //set i2c clock speed of 400KHZ
  Wire.setClock(400000); 
  Wire.begin();

  //set to power mode, all sleep function disable
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00); 
  Wire.endTransmission();

  //low pass filter for both sensor
  Wire.beginTransmission(0x68);
  Wire.write(0x1A);
  Wire.write(0x05);
  Wire.endTransmission();
}
void IMU_MPU6050::setGyro(){
  Wire.beginTransmission(0x68);
  Wire.write(0x45); //just access the register
  Wire.endTransmission();

  Wire.requestFrom(0x68, 2); //pull 2 byte for gyroY
  int16_t gyro = Wire.read() << 8 | Wire.read(); //signed 16 bit integer
  gyro += m_gyro_offset*m_gyro_offsetGain; //offset raw value

  gyroRate = (float) gyro/m_gyroLSB + m_gyroRate_offset; //nudging a lil 
}
void IMU_MPU6050::setAccel(){
  Wire.beginTransmission(0x68);
  Wire.write(0x3B); //just access the accel register
  Wire.endTransmission();

  Wire.requestFrom(0x68, 6); //pull 6 byte, neglect acccelY
  int16_t accelX_LSB = Wire.read() << 8 | Wire.read(); //signed 16 bit integer
  // int16_t accelY_LSB = Wire.read() << 8 | Wire.read(); //signed 16 bit integer
  Wire.read();
  Wire.read();
  int16_t accelZ_LSB = Wire.read() << 8 | Wire.read(); //signed 16 bit integer
  accelX = (float) accelX_LSB/m_accelLSB + m_accelX_offset; //change 0.06 to + accel_offset
  // accelY = (float) accelY_LSB/accelLSB + 0.03;
  accelZ = (float) accelZ_LSB/m_accelLSB + m_accelZ_offset;

  accelAngle = atan2(accelX, accelZ)*RAD_TO_DEG + m_accelAngle_offset;

}

void IMU_MPU6050::setupGyro(){
  //Change sensitivity to mode 2
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x16);
  Wire.endTransmission();
}

void IMU_MPU6050::setupAccel(){
  //Change sensitivity to mode 2
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x16);
  Wire.endTransmission();
}

void IMU_MPU6050::setAllAccel(){
  Wire.beginTransmission(0x68);
  Wire.write(0x3B); //just access the accel register
  Wire.endTransmission();

  Wire.requestFrom(0x68, 6); //pull 6 byte, neglect acccelY
  int16_t accelX_LSB = Wire.read() << 8 | Wire.read(); //signed 16 bit integer
  int16_t accelY_LSB = Wire.read() << 8 | Wire.read(); //signed 16 bit integer
  int16_t accelZ_LSB = Wire.read() << 8 | Wire.read(); //signed 16 bit integer
  accelX = (float) accelX_LSB/m_accelLSB; //change 0.06 to + accel_offset
  accelY = (float) accelY_LSB/m_accelLSB;
  accelZ = (float) accelZ_LSB/m_accelLSB;
}