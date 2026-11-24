#include "Motor_module.h"


MOTOR_NEMA17::MOTOR_NEMA17(int Lmotor_step, int Lmotor_dir, int Rmotor_step, int Rmotor_dir, int ms1, int ms2, int ms3){
    m_Lmotor_step = Lmotor_step;
    m_Lmotor_dir = Lmotor_dir;
    m_Rmotor_step = Rmotor_step;
    m_Rmotor_dir = Rmotor_dir;
    m_ms1 = ms1;
    m_ms2 = ms2;
    m_ms3 = ms3;
}
void MOTOR_NEMA17::setPWM_frequency(float PWM_frequency){
    //handle near 0, timer 1 maxperiod 8388480. ~ 0.2 Hz
    if (PWM_frequency >= -m_deadzone && PWM_frequency <= m_deadzone){ //In the range [-0.2 , 0.2] -> Equivalent to 0
        Timer1.disablePwm(m_Lmotor_step);
        Timer1.disablePwm(m_Rmotor_step);
    } else if (PWM_frequency > 0){
        int m_motor_dutyCycle = 1000000/fabs(PWM_frequency);
        digitalWrite(m_Lmotor_dir, m_positiveYaxis[0]);
        digitalWrite(m_Rmotor_dir, m_positiveYaxis[1]);

        Timer1.pwm(m_Lmotor_step, m_dutyCycle, m_motor_dutyCycle);
        Timer1.pwm(m_Rmotor_step, m_dutyCycle, m_motor_dutyCycle);
    } else {
        int m_motor_dutyCycle = 1000000/fabs(PWM_frequency);
        digitalWrite(m_Lmotor_dir, m_negativeYaxis[0]);
        digitalWrite(m_Rmotor_dir, m_negativeYaxis[1]);

        Timer1.pwm(m_Lmotor_step, m_dutyCycle, m_motor_dutyCycle);
        Timer1.pwm(m_Rmotor_step, m_dutyCycle, m_motor_dutyCycle);
    }

}
void MOTOR_NEMA17::begin(){
    setupMotorPin();
    setupTimer1();
}
void MOTOR_NEMA17::setupMotorPin(){
  pinMode(m_Lmotor_step, OUTPUT);
  pinMode(m_Lmotor_dir, OUTPUT);
  pinMode(m_Rmotor_step, OUTPUT);
  pinMode(m_Rmotor_dir, OUTPUT);
  pinMode(m_ms1, OUTPUT);
  pinMode(m_ms2, OUTPUT);
  pinMode(m_ms3, OUTPUT);    

  //default state of pins
  digitalWrite(m_Lmotor_dir, m_positiveYaxis[0]);
  digitalWrite(m_Rmotor_dir, m_positiveYaxis[1]);
  digitalWrite(m_ms1, HIGH);
  digitalWrite(m_ms2, HIGH);
  digitalWrite(m_ms3, HIGH);
}

void MOTOR_NEMA17::setupTimer1(){
    Timer1.initialize(m_timer_initializing_period);

    Timer1.disablePwm(m_Lmotor_step);
    Timer1.disablePwm(m_Rmotor_step);
}