#include <SensoringPublisher.hpp>

SensoringPublisher::SensoringPublisher(std::shared_ptr<zenoh::Session> session)
{
    session_ = session;

    speed_pub.emplace(
        session_->declare_publisher(zenoh::KeyExpr("Vehicle/1/Speed")));
    current_voltage_pub.emplace(session_->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Powertrain/TractionBattery/CurrentVoltage")));
    current_current_pub.emplace(session_->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Powertrain/TractionBattery/CurrentCurrent")));
    current_power_pub.emplace(session_->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Powertrain/TractionBattery/CurrentPower")));
    state_of_charge_pub.emplace(session_->declare_publisher(
        zenoh::KeyExpr("Vehicle/1/Powertrain/TractionBattery/StateOfCharge")));
}

void SensoringPublisher::publishSpeed(float speed)
{
    speed_pub->put(std::to_string(speed));
}

void SensoringPublisher::publishCurrentVoltage(float voltage)
{
    current_voltage_pub->put(std::to_string(voltage));
}

void SensoringPublisher::publishCurrentCurrent(float current)
{
    current_current_pub->put(std::to_string(current));
}

void SensoringPublisher::publishCurrentPower(float power)
{
    current_power_pub->put(std::to_string(power));
}

void SensoringPublisher::publishStateOfCharge(float state_of_charge)
{
    state_of_charge_pub->put(std::to_string(state_of_charge));
}
