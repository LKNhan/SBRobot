#include "General.h"

void GENERAL::begin(){
    //Serial setup
    Serial.begin(m_baudrate);

    //Time counter setup
    m_previous_time = micros();
}

void GENERAL::setTime(){
  m_current_time = micros();
  dt = (double) (m_current_time - m_previous_time)/ 1000000;
  m_previous_time = micros();
}

void GENERAL::serialOut(String name, double value){
    Serial.print(">" + name + ":");
    Serial.println(value);
}