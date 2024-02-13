#ifndef PARTICLE_H
#define PARTICLE_H

#include<cstdint>

#include "physics_backend.hpp"
#include <QPoint>

namespace qtParticle
{

using Pixels = uint32_t;

struct Metadata
{
    Pixels radius;
};

QPoint toQPoint(
    physics::euler::Particle<physics::units::SI> const& particle,
    std::pair<Pixels, Pixels> const& windowSize);

physics::euler::Particle<physics::units::SI> spawnParticle(
    QPoint const& position,
    Pixels radius,
    std::pair<Pixels, Pixels> const& windowSize);

} // namespace qtParticle

#endif // PARTICLE_H
