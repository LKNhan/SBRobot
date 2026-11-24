#include "Control_module.h"

PID::PID(float Kp, float Ki, float Kd){
    m_Kp = Kp;
    m_Ki = Ki;
    m_Kd = Kd;
}
void PID::setPID(float currAngle, float targetAngle, double dt){
  m_E = currAngle - targetAngle;
  m_iE += m_E*dt;
  m_dE = (m_E-m_prevE)/dt;
  m_prevE = m_E;
  PID_value = m_Kp*m_E + m_Ki*m_iE + m_Kd*m_dE;
}