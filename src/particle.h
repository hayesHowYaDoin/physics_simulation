#ifndef PARTICLE_H
#define PARTICLE_H

#include <cstdint>

#include "physics_backend.hpp"
#include <QPoint>

namespace qtParticle
{

using Pixels = uint32_t;

struct Color
{
    uint16_t r;
    uint16_t g;
    uint16_t b;
};

struct Metadata
{
    Color color;
};

Pixels metersToPixels(physics::units::SI::Length meters);

physics::units::SI::Length pixelsToMeters(Pixels pixels);

QPoint toQPoint(
    physics::domain::PositionVector2D<physics::units::SI::Length> const& position,
    std::pair<Pixels, Pixels> const& windowSize);

physics::domain::PositionVector2D<physics::units::SI::Length> toPositionVector(
    QPoint const& position,
    std::pair<Pixels, Pixels> const& windowSize);

physics::euler::Particle<physics::units::SI> spawnParticle(
    QPoint const& position,
    Pixels radius,
    std::pair<Pixels, Pixels> const& windowSize);

} // namespace qtParticle

#endif // PARTICLE_H
