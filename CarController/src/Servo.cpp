#include "../include/Servo.hpp"

Servo::Servo() : m_currDirection(90) {}

Servo::~Servo() {}

void Servo::init(PCA9685* servoPCA)
{
    this->m_ServoPCA = servoPCA;
}

void Servo::setDirection(uint8_t angle)
{
    angle = std::clamp(static_cast<int>(angle), 0, 180);

    if (m_currDirection == angle)
    {
        return;
    }
    else
    {
        m_currDirection = angle;
    }

    uint16_t pulseWidth = static_cast<uint16_t>(205 + (angle * 205) / 180);
    m_ServoPCA->setPWM(0, 0, pulseWidth);
}