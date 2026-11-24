#include "SensorFusion_module.h"

COMPLEMENTARY_FILTER::COMPLEMENTARY_FILTER(float a){
    m_a = a;
}
void COMPLEMENTARY_FILTER::setCurrAngle(float gyroRate, float accelAngle, double dt){
    currAngle = m_a*(currAngle + gyroRate*dt) + (1-m_a)*(accelAngle); //sensor fusion
}