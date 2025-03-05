#include <catch2/catch_test_macros.hpp>
#include "MotionManagement.hpp"

TEST_CASE("MotionManagement Integration Tests", "[motion_management]")
{
    MotionManagement management;

    SECTION("Electric Axle Integration")
    {
        ElectricAxle axle;
        auto& row1 = axle.get_mutable_row1();
        row1.set_rotational_speed(1500);
        row1.set_rotational_speed_target(1800);

        management.set_electric_axle(axle);
        REQUIRE(
            management.get_electric_axle().get_row1().get_rotational_speed() ==
            1500);
        REQUIRE(management.get_electric_axle()
                    .get_row1()
                    .get_rotational_speed_target() == 1800);

        auto& mutable_axle = management.get_mutable_electric_axle();
        mutable_axle.get_mutable_row1().set_rotational_speed(2000);
        REQUIRE(
            management.get_electric_axle().get_row1().get_rotational_speed() ==
            2000);
    }

    SECTION("Steering Integration")
    {
        Steering steering;
        auto& wheel = steering.get_mutable_steering_wheel();
        wheel.set_angle(30.0f);
        wheel.set_angle_target(45.0f);

        management.set_steering(steering);
        REQUIRE(management.get_steering().get_steering_wheel().get_angle() ==
                Approx(30.0f));
        REQUIRE(
            management.get_steering().get_steering_wheel().get_angle_target() ==
            Approx(45.0f));
    }
}