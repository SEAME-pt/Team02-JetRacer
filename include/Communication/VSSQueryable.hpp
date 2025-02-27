#pragma once

#include "Vehicle.hpp"
#include <zenoh.hxx>
#include <optional>

class VSSQueryable
{
  public:
    VSSQueryable(Vehicle& vehicle);

  private:
    Vehicle& vehicle_;
    std::unique_ptr<zenoh::Session> session;
    std::optional<zenoh::Queryable<void>> throttle_queryable;
    std::optional<zenoh::Queryable<void>> steering_queryable;
    std::optional<zenoh::Queryable<void>> beamLow_queryable;
    std::optional<zenoh::Queryable<void>> beamHigh_queryable;
    std::optional<zenoh::Queryable<void>> running_queryable;
    std::optional<zenoh::Queryable<void>> parking_queryable;
    std::optional<zenoh::Queryable<void>> fogRear_queryable;
    std::optional<zenoh::Queryable<void>> fogFront_queryable;
    std::optional<zenoh::Queryable<void>> brake_queryable;
    std::optional<zenoh::Queryable<void>> hazard_queryable;
    std::optional<zenoh::Queryable<void>> directionIndicatorLeft_queryable;
    std::optional<zenoh::Queryable<void>> directionIndicatorRight_queryable;
};
