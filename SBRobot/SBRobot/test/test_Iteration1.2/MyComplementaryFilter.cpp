#include <Arduino.h>
#include <Wire.h>

float accelX_offset = -3494, accelZ_offset = 949;
float accelX, accelY, accelZ;
float accelLSB = 4096.0;
float accel_offsetGain = 0;
float accelAngle = 0;

float gyro_rate = 0;
float gyro_offset = -19;
float gyroLSB = 32.8;
float gyro_offsetGain = 1;
float gyroAngle = 0;


float dt = 0, current_time, previous_time;

float currAngle = 0;
float a = 0.98;

void setupGyro(){
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
  Wire.write(0x1B);
  Wire.write(0x16);
  Wire.endTransmission();
}
void setupAccel(){
  Wire.setClock(400000); //max clock speed of 400KHZ
  Wire.begin();

  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00); //set to power mode, all sleep function disable
  Wire.endTransmission();

  //Set i2c to adress of IMU
  Wire.beginTransmission(0x68);
  //Low pass for accel
  Wire.write(0x1A);
  Wire.write(0x05);
  Wire.endTransmission();

  //Change sensitivity to mode 2
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x16);
  Wire.endTransmission();
}
void getGyro(){
  Wire.beginTransmission(0x68);
  Wire.write(0x45); //just access the register
  Wire.endTransmission();

  Wire.requestFrom(0x68, 2); //pull 2 byte for gyroY
  int16_t gyro = Wire.read() << 8 | Wire.read(); //signed 16 bit integer
  gyro += gyro_offset*gyro_offsetGain;

  gyro_rate = (float)gyro/gyroLSB;

}
void getAccel(){
  Wire.beginTransmission(0x68);
  Wire.write(0x3B); //just access the accel register
  Wire.endTransmission();

  Wire.requestFrom(0x68, 6); //pull 6 byte, neglect acccelY
  int16_t accelX_LSB = Wire.read() << 8 | Wire.read(); //signed 16 bit integer
  // int16_t accelY_LSB = Wire.read() << 8 | Wire.read(); //signed 16 bit integer
  Wire.read();
  Wire.read();
  int16_t accelZ_LSB = Wire.read() << 8 | Wire.read(); //signed 16 bit integer
  // accelX_LSB += accelX_offset*accel_offsetGain;
  // accelY_LSB += accelY_offset*accel_offsetGain;
  // accelZ_LSB += accelZ_offset*accel_offsetGain;

  accelX = (float) accelX_LSB/accelLSB - 0.06;
  // accelY = (float) accelY_LSB/accelLSB + 0.03;
  accelZ = (float) accelZ_LSB/accelLSB - 0.09;

  accelAngle = atan2(accelX, accelZ)*RAD_TO_DEG-0.08;
}
void getTime (){
  current_time = micros();
  dt = (float) (current_time - previous_time)/ 1000000.0;
  previous_time = micros();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(250);

  setupAccel();
  setupGyro();
  previous_time = micros();
}

void loop() {
  // put your main code here, to run repeatedly:
  getTime();
  getAccel();
  getGyro();
  currAngle = a*(currAngle + gyro_rate*dt) + (1-a)*(accelAngle);




  Serial.print("accelAngle:");
  Serial.print(accelAngle);
  Serial.print(", ");
  Serial.print("gyrorate:");
  Serial.print(gyro_rate);
  Serial.print(", ");
  Serial.print("currAngle:");
  Serial.print(currAngle);
  Serial.println();

}
