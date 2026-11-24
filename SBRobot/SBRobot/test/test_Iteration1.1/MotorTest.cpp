/*
CW, CWW for each motor, remain communicaiton.
2 button for changing direction

1: CCW for LMotor
2: CW for LMotor 
3: CCW for RMotor 
4: CW for RMotor

*/

//define all the pins
#include <Arduino.h>
//Setup for motor
int LMotor_Step = 9;
int LMotor_Dir = 8;
int RMotor_Step = 7;
int RMotor_Dir = 6;

int ms1 = 4;
int ms2 = 3;
int ms3 = 11;

int counterClockwise = 1;
int Clockwise = 0;


//Rotate for how many steps
void Rotate(int motor, int directionPin, int direction, int stepCount, int delayDuration){
  digitalWrite(directionPin, direction);
  for (int i = 0; i < stepCount; i++){
    digitalWrite(motor, HIGH);
    delayMicroseconds(delayDuration); //might be weakpoint cuz it stop the program
    digitalWrite(motor, LOW);
    delayMicroseconds(delayDuration);
  }
}

void Microstep(int resolution){
  switch (resolution){
    case 1:
      digitalWrite(ms1, LOW);
      digitalWrite(ms2, LOW);
      digitalWrite(ms3, LOW);
      break;
    case 2:
      digitalWrite(ms1, HIGH);
      digitalWrite(ms2, LOW);
      digitalWrite(ms3, LOW);
      break;
    case 4:
      digitalWrite(ms1, LOW);
      digitalWrite(ms2, HIGH);
      digitalWrite(ms3, LOW);
      break;
    case 8:
      digitalWrite(ms1, HIGH);
      digitalWrite(ms2, HIGH);
      digitalWrite(ms3, LOW);
      break;
    case 16:
      digitalWrite(ms1, HIGH);
      digitalWrite(ms2, HIGH);
      digitalWrite(ms3, HIGH);
      break;
  }
}
void setup() {
  Serial.begin(9600);
  Serial.println("Motor testing program");
  pinMode(LMotor_Step, OUTPUT);
  pinMode(LMotor_Dir, OUTPUT);
  pinMode(RMotor_Step, OUTPUT);
  pinMode(RMotor_Dir, OUTPUT);

  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(ms3, OUTPUT);
  
  digitalWrite(LMotor_Dir, HIGH);
  digitalWrite(RMotor_Dir, HIGH);

  digitalWrite(ms1, LOW);
  digitalWrite(ms2, LOW);
  digitalWrite(ms3, LOW);
}

void loop() {
  if (Serial.available()){
    char message = Serial.read();
      switch (message){
    case '1':
      Rotate(LMotor_Step, LMotor_Dir, counterClockwise, 200, 2000);
      Serial.println("Rotate Left motor counter clockwise by 200 step");
      break;
    case '2':
      Rotate(LMotor_Step, LMotor_Dir, Clockwise, 200, 2000);
      Serial.println("Rotate Left motor clockwise by 200 step");
      break;
    case '3':
      Rotate(RMotor_Step, RMotor_Dir, counterClockwise, 200, 2000);
      Serial.println("Rotate Right motor counter clockwise by 200 step");
      break;
    case '4':
      Rotate(RMotor_Step, RMotor_Dir, Clockwise, 200, 2000);
      Serial.println("Rotate Right motor clockwise by 200 step");
      break;
    case '5':
      Microstep(1);
      break;
    case '6':
      Microstep(2);
      break;
    case '7':
      Microstep(4);
      break;
    case '8':
      Microstep(8);
      break;
    case '9':
      Microstep(16);
      break;
    }
  }
  

}
