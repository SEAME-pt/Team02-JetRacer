#include "VehicleSystem.hpp"

int main()
{
    // Start vehicle system
    VehicleSystem system;

    // Main loop
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}