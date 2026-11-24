/*
Goal: 
- Connect to bluetooth
- Get the signal from the app, print to serial monitor

I know the process is like:

The bluetooth module will sent back a string to the serial, gotta extract it out
serial.read character by character
a command ends with a \n
If receive: LmotorCW then print sth out
If receive: RmotorCWW then print sth out
I will do it a little bit messy at first then clean up everything by putting it in a function
*/
String message = "";

void setup() {
  Serial.begin(9600); //like default for HC-05
  Serial.println("The bluetooth testing program is initializing.....");
}

void loop() {
  char incomingChar = Serial.read();
  if (Serial.available()){ //check in the serial buffer check if incoming >0
    message += incomingChar; //record
    Serial.println("The receive message is: " + message);
    if (incomingChar == '0'){
      message = "";
    }
  }
  if (message == "Rmotor_CCW"){
    Serial.print("Right motor: Turn counter clockwise");
  }
  if (message == "Rmotor_CW"){
    Serial.print("Right motor: Turn clockwise");
  }
  if (message == "Lmotor_CCW"){
    Serial.print("Left motor: Turn counter clockwise");
  }
  if (message == "Lmotor_CW"){
    Serial.print("Left motor: Turn clockwise");
  }
  delay(20);
}
