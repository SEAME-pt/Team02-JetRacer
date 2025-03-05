#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Vehicle.hpp"

TEST_CASE("Vehicle Tests", "[vehicle]")
{
    Vehicle vehicle;

    SECTION("Basic Properties Tests")
    {
        vehicle.set_average_speed(60.5f);
        REQUIRE_THAT(vehicle.get_average_speed(),
                     Catch::Matchers::WithinRel(60.5f, 0.001f));

        vehicle.set_current_overall_weight(1500);
        REQUIRE(vehicle.get_current_overall_weight() == 1500);

        vehicle.set_height(1450);
        REQUIRE(vehicle.get_height() == 1450);

        vehicle.set_length(4200);
        REQUIRE(vehicle.get_length() == 4200);

        vehicle.set_is_moving(true);
        REQUIRE(vehicle.get_is_moving() == true);
    }

    SECTION("Movement Tests")
    {
        vehicle.set_speed(100.5f);
        REQUIRE_THAT(vehicle.get_speed(),
                     Catch::Matchers::WithinRel(100.5f, 0.001f));

        vehicle.set_traveled_distance(150.75f);
        REQUIRE_THAT(vehicle.get_traveled_distance(),
                     Catch::Matchers::WithinRel(150.75f, 0.001f));

        vehicle.set_trip_duration(3600.0f);
        REQUIRE_THAT(vehicle.get_trip_duration(),
                     Catch::Matchers::WithinRel(3600.0f, 0.001f));

        vehicle.set_turning_diameter(11000);
        REQUIRE(vehicle.get_turning_diameter() == 11000);
    }

    SECTION("Component Integration Tests")
    {
        auto& powertrain = vehicle.get_mutable_powertrain();
        powertrain.get_mutable_electric_motor().set_speed(120);
        REQUIRE(vehicle.get_powertrain().get_electric_motor().get_speed() ==
                120);

        auto& chassis = vehicle.get_mutable_chassis();
        chassis.set_wheelbase(2700);
        REQUIRE(vehicle.get_chassis().get_wheelbase() == 2700);
    }
}