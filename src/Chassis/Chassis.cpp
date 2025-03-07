#include "Chassis.hpp"

const Accelerator& Chassis::get_accelerator() const
{
    return accelerator;
}
Accelerator& Chassis::get_mutable_accelerator()
{
    return accelerator;
}
void Chassis::set_accelerator(const Accelerator& value)
{
    this->accelerator = value;
}

const Axle& Chassis::get_axle() const
{
    return axle;
}
Axle& Chassis::get_mutable_axle()
{
    return axle;
}
void Chassis::set_axle(const Axle& value)
{
    this->axle = value;
}

std::uint8_t Chassis::get_axle_count() const
{
    return axle_count;
}

void Chassis::set_axle_count(const std::uint8_t value)
{
    this->axle_count = value;
}

const Brake& Chassis::get_brake() const
{
    return brake;
}
Brake& Chassis::get_mutable_brake()
{
    return brake;
}
void Chassis::set_brake(const Brake& value)
{
    this->brake = value;
}

const ChassisSteeringWheel& Chassis::get_steering_wheel() const
{
    return steering_wheel;
}
ChassisSteeringWheel& Chassis::get_mutable_steering_wheel()
{
    return steering_wheel;
}
void Chassis::set_steering_wheel(const ChassisSteeringWheel& value)
{
    this->steering_wheel = value;
}

std::uint16_t Chassis::get_wheelbase() const
{
    return wheelbase;
}

void Chassis::set_wheelbase(const std::uint16_t value)
{
    this->wheelbase = value;
}
