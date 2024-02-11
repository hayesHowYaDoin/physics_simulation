#ifndef PARTICLE_H
#define PARTICLE_H

#include "physics_backend.hpp"
#include <QPoint>

#include "metadata.h"

namespace qtParticle
{

namespace
{

constexpr float pixelsToMeters {4.0};

} // namespace

QPoint toQPoint(physics::euler::Particle<physics::units::SI> const& particle)
{
    auto x {particle.position.getX<physics::units::meters<double>>()};
    auto y {particle.position.getY<physics::units::meters<double>>()};

    return QPoint(x.to<double>()*pixelsToMeters, y.to<double>()*pixelsToMeters);
}

physics::euler::Particle<physics::units::SI> spawnParticle(QPoint const& position, int radius)
{
    using namespace physics::units;
    using namespace physics::units::literals;

    meters<double> x {meters<double>(position.x()/pixelsToMeters)};
    meters<double> y {meters<double>(position.y()/pixelsToMeters)};

    return physics::euler::Particle<SI>{
        .mass {1.0_kg},
        .position {Vector2D::fromComponents(x, y)},
        .velocity {Vector2D::fromComponents(0.0_mps, 0.0_mps)},
        .forces {Vector2D::fromComponents(0.0_N, -9.81_N)},
        .metadata {Metadata{.radius = radius}}
    };
}

} // namespace qtParticle

#endif // PARTICLE_H
