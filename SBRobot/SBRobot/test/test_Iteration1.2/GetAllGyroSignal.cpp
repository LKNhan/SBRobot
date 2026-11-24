#include <Arduino.h>
#include <Wire.h>

float gyroX_rate, gyroY_rate, gyroZ_rate;
float gyroX_offset = 50, gyroY_offset = -19, gyroZ_offset = -1;
float gyroLSB = 32.8;
float gyro_offsetGain = 1;

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
  Wire.write(0x43); //just access the register
  Wire.endTransmission();

  Wire.requestFrom(0x68, 6); //pull 6 byte out
  int16_t gyroX = Wire.read() << 8 | Wire.read(); //signed 16 bit integer
  int16_t gyroY = Wire.read() << 8 | Wire.read();
  int16_t gyroZ = Wire.read() << 8 | Wire.read();
  gyroX += gyroX_offset*gyro_offsetGain;
  gyroY += gyroY_offset*gyro_offsetGain;
  gyroZ += gyroZ_offset*gyro_offsetGain;

  gyroX_rate = (float)gyroX/gyroLSB;
  gyroY_rate = (float)gyroY/gyroLSB;
  gyroZ_rate = (float)gyroZ/gyroLSB;

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(250);

  setupGyro();
}

void loop() {
  // put your main code here, to run repeatedly:
  getGyro();
  Serial.print("RateX:");
  Serial.print(gyroX_rate);
  Serial.print(", ");
  Serial.print("RateY:");
  Serial.print(gyroY_rate);
  Serial.print(", ");
  Serial.print("rateZ:");
  Serial.print(gyroZ_rate);
  Serial.println();

}
