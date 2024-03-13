#include <algorithm>
#include <cmath>
#include <random>
#include <vector>

#include "particle.h"

namespace qtParticle
{

namespace
{

constexpr double PIXELS_PER_METER {20.0};

std::random_device rd;  // a seed source for the random number engine
std::mt19937 gen(rd());

Color generateSaturatedColor()
{
    std::uniform_int_distribution<> colorDist(0, 255);
    auto colorGen = [&colorDist](){
        return static_cast<decltype(std::declval<Color>().r)>(colorDist(gen));
    };

    std::vector<size_t> remainingIndices {0, 1, 2};
    auto indexGen = [&remainingIndices](){
        std::uniform_int_distribution<> indexDist(0, remainingIndices.size() - 1);
        size_t index {remainingIndices.at(indexDist(gen))};

        remainingIndices.erase(std::remove(remainingIndices.begin(), remainingIndices.end(), index), remainingIndices.end());
        return index;
    };

    std::array<uint16_t, 3> color {colorGen(), colorGen(), colorGen()};
    color.at(indexGen()) = 0;
    color.at(indexGen()) = 255;

    return {.r = color.at(0), .g = color.at(1), .b = color.at(2)};
}

} // namespace

Pixels metersToPixels(physics::units::SI::Length meters)
{
    return meters.to<double>() * PIXELS_PER_METER;
}

physics::units::SI::Length pixelsToMeters(Pixels pixels)
{
    return physics::units::SI::Length(pixels / PIXELS_PER_METER);
}

QPoint toQPoint(
    physics::domain::PositionVector2D<physics::units::SI::Length> const& position,
    std::pair<Pixels, Pixels> const& windowSize)
{
    auto x_m {position.getX<physics::units::meters<double>>()};
    auto y_m {position.getY<physics::units::meters<double>>()};

    Pixels x_px {static_cast<Pixels>(std::floor(windowSize.first - x_m.to<double>() * PIXELS_PER_METER))};
    Pixels y_px {static_cast<Pixels>(std::floor(windowSize.second - y_m.to<double>() * PIXELS_PER_METER))};

    return QPoint(x_px, y_px);
}

physics::domain::PositionVector2D<physics::units::SI::Length> toPositionVector(
    QPoint const& position,
    std::pair<Pixels, Pixels> const& windowSize)
{
    using namespace physics::units;
    using namespace physics::units::literals;

    Pixels x_px {static_cast<Pixels>(position.x())};
    Pixels y_px {static_cast<Pixels>(position.y())};

    meters<double> x_m {(windowSize.first - x_px) / PIXELS_PER_METER};
    meters<double> y_m {(windowSize.second - y_px) / PIXELS_PER_METER};

    return physics::domain::Vector2D::fromComponents(x_m, y_m);
}

physics::euler::Particle<physics::units::SI> spawnParticle(
    QPoint const& position,
    Pixels radius,
    std::pair<Pixels, Pixels> const& windowSize)
{
    using namespace physics::units;
    using namespace physics::units::literals;

    std::uniform_int_distribution<> velocityDistrib(-20, 20);
    auto vX {physics::units::velocity::meters_per_second<double>(velocityDistrib(gen))};
    auto vY {physics::units::velocity::meters_per_second<double>(velocityDistrib(gen))};

    Color color {generateSaturatedColor()};

    return physics::euler::Particle<SI>{
        .mass {1.0_kg},
        .radius {SI::Length(static_cast<double>(radius) / PIXELS_PER_METER)},
        .position {toPositionVector(position, windowSize)},
        .velocity {physics::domain::Vector2D::fromComponents(vX, vY)},
        .forces {physics::domain::Vector2D::fromComponents(0.0_N, 0.0_N)},
        .metadata {Metadata{.color = color}}
    };
}

} // namespace qtParticle
