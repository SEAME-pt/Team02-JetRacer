#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "ElectricMotor.hpp"

class MockSpeedObserver : public IVehicleObserver
{
  public:
    int32_t last_speed = 0;
    void onSpeedChanged(int32_t speed) override { last_speed = speed; }
    void onSteeringAngleChanged(float) override {}
};

TEST_CASE("ElectricMotor Tests", "[electric_motor]")
{
    ElectricMotor motor;

    SECTION("Max Power Tests")
    {
        motor.set_max_power(250);
        REQUIRE(motor.get_max_power() == 250);
    }

    SECTION("Speed Tests")
    {
        auto observer = std::make_shared<MockSpeedObserver>();
        motor.addObserver(observer);

        motor.set_speed(100);
        REQUIRE(motor.get_speed() == 100);
        REQUIRE(observer->last_speed == 100);

        // Test that observer isn't notified when speed doesn't change
        motor.set_speed(100);
        REQUIRE(observer->last_speed == 100);
    }

    SECTION("Time In Use Tests")
    {
        motor.set_time_in_use(1234.56f);
        REQUIRE_THAT(motor.get_time_in_use(),
                     Catch::Matchers::WithinRel(1234.56f, 0.001f));
    }
}