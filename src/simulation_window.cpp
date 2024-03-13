#include <QPainter>
#include <QTimer>

#include "simulation_window.h"
#include "ui_simulation_window.h"

using namespace physics::units::literals;

SimulationWindow::SimulationWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::SimulationWindow),
    m_constraint {{
        qtParticle::toPositionVector({0, 0}, m_windowSize),
        qtParticle::toPositionVector({m_windowSize.first, 0}, m_windowSize),
        qtParticle::toPositionVector({m_windowSize.first, m_windowSize.second}, m_windowSize),
        qtParticle::toPositionVector({0, m_windowSize.second}, m_windowSize),
      }}
{
    setFixedSize(m_windowSize.first, m_windowSize.second);
    ui->setupUi(this);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SimulationWindow::stepSimulation);
    timer->start(m_frameRate);
}

SimulationWindow::~SimulationWindow()
{
    delete ui;
}

void SimulationWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint point {event->pos()};
    qtParticle::Pixels radius {20};

    physics::euler::Particle<physics::units::SI> particle {qtParticle::spawnParticle(point, radius, m_windowSize)};
    m_particles.push_back(particle);
}

void SimulationWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));

    for (auto const& particle : m_particles)
    {
        QPoint point {qtParticle::toQPoint(particle.position, m_windowSize)};
        qtParticle::Pixels radius {qtParticle::metersToPixels(particle.radius)};

        qtParticle::Metadata data {std::any_cast<qtParticle::Metadata>(particle.metadata)};
        painter.drawEllipse(point, radius, radius); // center, width, height
    }
}

void SimulationWindow::stepSimulation()
{
    m_particles = physics::euler::step(m_particles, m_constraint, physics::units::time::milliseconds<double>(m_frameRate));
    update();
}
