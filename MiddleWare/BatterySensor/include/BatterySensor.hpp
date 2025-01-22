
#pragma once

#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include "I2C.hpp"
#include "INA219.hpp"
#include "CAN.hpp"
#include "zenoh.hxx"

using namespace zenoh;

extern int signalTo;

class BatterySensor
{ 
    private:
        I2C* m_I2c;
        INA219* batteryINA;
        CAN* canBus;
        Session m_session;
        Publisher m_pubBattery;
        double smoothedVoltage;


    public:
    BatterySensor();
    ~BatterySensor();

    void init(const std::string& i2cDevice, uint8_t sensorAddress, const std::string& canDevice);
    void run( void );
};
