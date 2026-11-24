#ifndef CONTROl_MODULE_H
#define CONTROL_MODULE_H

#include <Arduino.h>

class PID{
public: 
    PID(float Kp, float Ki, float Kd);
    float PID_value = 0;
    void setPID(float currAngle, float targetAngle, double dt);
private:
    float m_prevE = 0;
    float m_E=0;
    float m_iE=0;
    float m_dE=0;
    
    float m_Kp = 0; //1230
    float m_Ki = 0; //
    float m_Kd = 0; //40
    float m_Km = 1;
};

#endif
