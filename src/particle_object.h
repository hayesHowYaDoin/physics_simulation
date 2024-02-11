#ifndef PARTICLEOBJECT_H
#define PARTICLEOBJECT_H

#include <QPoint>

struct ParticleObject
{
    ParticleObject(QPoint position, int radius):
        m_position {position},
        m_radius {radius}
    {
        // Intentionally left blank
    }

    QPoint getPosition() const
    {
        return m_position;
    }

    int getRadius() const
    {
        return m_radius;
    }

private:
    QPoint m_position;
    int m_radius;
};

#endif // PARTICLEOBJECT_H
