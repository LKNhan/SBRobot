#include <Arduino.h>
#include <Wire.h>

//get gyro angle around y axis
float gyro_rate;
float gyro_offset = -19;
float gyroLSB = 32.8;
float gyro_offsetGain = 1;
float gyroAngle = 0;

float dt = 0, current_time, previous_time;

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
void getGyro(){
  Wire.beginTransmission(0x68);
  Wire.write(0x45); //just access the register
  Wire.endTransmission();

  Wire.requestFrom(0x68, 2); //pull 2 byte for gyroY
  int16_t gyro = Wire.read() << 8 | Wire.read(); //signed 16 bit integer
  gyro += gyro_offset*gyro_offsetGain;

  gyro_rate = (float)gyro/gyroLSB;

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

  setupGyro();

  previous_time = micros();
}

void loop() {
  // put your main code here, to run repeatedly:
  getTime();
  getGyro(); //update gyro rate global value
  gyroAngle += gyro_rate*dt;

  Serial.print("Gyro:");
  Serial.print(gyro_rate);
  Serial.print(", ");
  Serial.print("GyroAngle:");
  Serial.print(gyroAngle);
  Serial.println();

}
