#ifndef GENERAL_H
#define GENERAL_H

#include <Arduino.h>

class GENERAL{
public:
    double dt;

    void begin();
    void setTime();
    void serialOut(String name, double value);
private:
    unsigned long m_baudrate = 115200;
    unsigned long m_previous_time, m_current_time;
};

#endif