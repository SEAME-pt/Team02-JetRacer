#include <catch2/catch_test_macros.hpp>
#include "Lights.hpp"

TEST_CASE("SignalingLights Tests", "[lights]")
{
    SignalingLights signal;

    SECTION("Defect State Tests")
    {
        signal.set_is_defect(true);
        REQUIRE(signal.get_is_defect() == true);
        signal.set_is_defect(false);
        REQUIRE(signal.get_is_defect() == false);
    }

    SECTION("Signaling State Tests")
    {
        signal.set_is_signaling(true);
        REQUIRE(signal.get_is_signaling() == true);
        signal.set_is_signaling(false);
        REQUIRE(signal.get_is_signaling() == false);
    }
}

TEST_CASE("StaticLights Tests", "[lights]")
{
    StaticLights static_light;

    SECTION("Defect State Tests")
    {
        static_light.set_is_defect(true);
        REQUIRE(static_light.get_is_defect() == true);
    }

    SECTION("On/Off State Tests")
    {
        static_light.set_is_on(true);
        REQUIRE(static_light.get_is_on() == true);
    }
}

TEST_CASE("BrakeLights Tests", "[lights]")
{
    BrakeLights brake;

    SECTION("Defect State Tests")
    {
        brake.set_is_defect(true);
        REQUIRE(brake.get_is_defect() == true);
    }

    SECTION("Active State Tests")
    {
        brake.set_is_active(true);
        REQUIRE(brake.get_is_active() == true);
    }
}

TEST_CASE("Lights Integration Tests", "[lights]")
{
    Lights lights;

    SECTION("Beam Lights Tests")
    {
        auto& beam_low = lights.get_mutable_beam_low();
        beam_low.set_is_on(true);
        REQUIRE(lights.get_beam_low().get_is_on() == true);

        auto& beam_high = lights.get_mutable_beam_high();
        beam_high.set_is_on(true);
        REQUIRE(lights.get_beam_high().get_is_on() == true);
    }

    SECTION("Direction Indicators Tests")
    {
        auto& left = lights.get_mutable_direction_indicator_left();
        left.set_is_signaling(true);
        REQUIRE(lights.get_direction_indicator_left().get_is_signaling() ==
                true);

        auto& right = lights.get_mutable_direction_indicator_right();
        right.set_is_signaling(true);
        REQUIRE(lights.get_direction_indicator_right().get_is_signaling() ==
                true);
    }

    SECTION("Fog Lights Tests")
    {
        auto& front = lights.get_mutable_fog_front();
        front.set_is_on(true);
        REQUIRE(lights.get_fog_front().get_is_on() == true);

        auto& rear = lights.get_mutable_fog_rear();
        rear.set_is_on(true);
        REQUIRE(lights.get_fog_rear().get_is_on() == true);
    }

    SECTION("Other Lights Tests")
    {
        auto& hazard = lights.get_mutable_hazard();
        hazard.set_is_signaling(true);
        REQUIRE(lights.get_hazard().get_is_signaling() == true);

        auto& parking = lights.get_mutable_parking();
        parking.set_is_on(true);
        REQUIRE(lights.get_parking().get_is_on() == true);

        auto& running = lights.get_mutable_running();
        running.set_is_on(true);
        REQUIRE(lights.get_running().get_is_on() == true);

        auto& brake = lights.get_mutable_brake();
        brake.set_is_active(true);
        REQUIRE(lights.get_brake().get_is_active() == true);
    }

    SECTION("Beam Lights Setter Tests")
    {
        StaticLights new_beam_low;
        new_beam_low.set_is_on(true);
        lights.set_beam_low(new_beam_low);
        REQUIRE(lights.get_beam_low().get_is_on() == true);

        StaticLights new_beam_high;
        new_beam_high.set_is_on(true);
        lights.set_beam_high(new_beam_high);
        REQUIRE(lights.get_beam_high().get_is_on() == true);
    }

    SECTION("Direction Indicators Setter Tests")
    {
        SignalingLights new_left;
        new_left.set_is_signaling(true);
        lights.set_direction_indicator_left(new_left);
        REQUIRE(lights.get_direction_indicator_left().get_is_signaling() ==
                true);

        SignalingLights new_right;
        new_right.set_is_signaling(true);
        lights.set_direction_indicator_right(new_right);
        REQUIRE(lights.get_direction_indicator_right().get_is_signaling() ==
                true);
    }

    SECTION("Fog Lights Setter Tests")
    {
        StaticLights new_front;
        new_front.set_is_on(true);
        lights.set_fog_front(new_front);
        REQUIRE(lights.get_fog_front().get_is_on() == true);

        StaticLights new_rear;
        new_rear.set_is_on(true);
        lights.set_fog_rear(new_rear);
        REQUIRE(lights.get_fog_rear().get_is_on() == true);
    }

    SECTION("Other Lights Setter Tests")
    {
        SignalingLights new_hazard;
        new_hazard.set_is_signaling(true);
        lights.set_hazard(new_hazard);
        REQUIRE(lights.get_hazard().get_is_signaling() == true);

        StaticLights new_parking;
        new_parking.set_is_on(true);
        lights.set_parking(new_parking);
        REQUIRE(lights.get_parking().get_is_on() == true);

        StaticLights new_running;
        new_running.set_is_on(true);
        lights.set_running(new_running);
        REQUIRE(lights.get_running().get_is_on() == true);

        BrakeLights new_brake;
        new_brake.set_is_active(true);
        lights.set_brake(new_brake);
        REQUIRE(lights.get_brake().get_is_active() == true);
    }
}