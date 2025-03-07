#include "Exterior.hpp"

float Exterior::get_air_temperature() const
{
    return air_temperature;
}
void Exterior::set_air_temperature(const float value)
{
    this->air_temperature = value;
}

float Exterior::get_humidity() const
{
    return humidity;
}
void Exterior::set_humidity(const float value)
{
    this->humidity = value;
}

float Exterior::get_light_intensity() const
{
    return light_intensity;
}
void Exterior::set_light_intensity(const float value)
{
    this->light_intensity = value;
}
