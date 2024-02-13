#include <cmath>

#include "particle.h"

namespace qtParticle
{

namespace
{

constexpr double PIXELS_PER_METER {20.0};

} // namespace

QPoint toQPoint(
    physics::euler::Particle<physics::units::SI> const& particle,
    std::pair<Pixels, Pixels> const& windowSize)
{
    auto x_m {particle.position.getX<physics::units::meters<double>>()};
    auto y_m {particle.position.getY<physics::units::meters<double>>()};

    Pixels x_px {static_cast<Pixels>(std::floor(windowSize.first - x_m.to<double>() * PIXELS_PER_METER))};
    Pixels y_px {static_cast<Pixels>(std::floor(windowSize.second - y_m.to<double>() * PIXELS_PER_METER))};

    return QPoint(x_px, y_px);
}

physics::euler::Particle<physics::units::SI> spawnParticle(
    QPoint const& position,
    Pixels radius,
    std::pair<Pixels, Pixels> const& windowSize)
{
    using namespace physics::units;
    using namespace physics::units::literals;

    Pixels x_px {static_cast<Pixels>(position.x())};
    Pixels y_px {static_cast<Pixels>(position.y())};

    meters<double> x_m {(windowSize.first - x_px) / PIXELS_PER_METER};
    meters<double> y_m {(windowSize.second - y_px) / PIXELS_PER_METER};

    return physics::euler::Particle<SI>{
        .mass {1.0_kg},
        .position {Vector2D::fromComponents(x_m, y_m)},
        .velocity {Vector2D::fromComponents(0.0_mps, 0.0_mps)},
        .forces {Vector2D::fromComponents(0.0_N, -9.81_N)},
        .metadata {Metadata{.radius = radius}}
    };
}

} // namespace qtParticle
