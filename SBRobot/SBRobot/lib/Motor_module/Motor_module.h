#ifndef MOTOR_MODULE_H
#define MOTOR_MODULE_H

#include <Arduino.h>
#include <TimerOne.h>
#include <math.h>

class MOTOR_NEMA17{
public: 
    //constructor doesn't need return type
    
    MOTOR_NEMA17(int Lmotor_step = 9, int Lmotor_dir = 8, int Rmotor_step = 10, int Rmotor_dir = 6, int ms1 = 4, int ms2 = 3, int ms3 = 11);
    void begin();
    void setPWM_frequency(float PWM_frequency);
private:
    void setupMotorPin();
    void setupTimer1();

    int m_timer_initializing_period = 10000; //fire interrupt at 10ms

    int m_dutyCycle = 512;

    uint8_t m_Lmotor_step = 9;
    uint8_t m_Lmotor_dir = 8;
    uint8_t m_Rmotor_step = 10;
    uint8_t m_Rmotor_dir = 6;
    uint8_t m_ms1 = 4;
    uint8_t m_ms2 = 3;
    uint8_t m_ms3 = 11;

    //for flipping direction of motor, change if got the direction wrong
    int m_positiveYaxis[2] = {0, 1};
    int m_negativeYaxis[2] = {1, 0};
    int m_deadzone = 30; //the range [-deadzone, deadzone] will be set to 0
};



#endif