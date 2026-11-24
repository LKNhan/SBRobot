#ifndef SENSORFUSION_MODULE_H
#define SENSORFUSION_MODULE_H

class COMPLEMENTARY_FILTER{
public:
    double currAngle = 0;
    COMPLEMENTARY_FILTER(float a);
    void setCurrAngle(float gyroRate, float accelAngle, double dt);

private:
    
    float m_a = 0.98;
};

#endif