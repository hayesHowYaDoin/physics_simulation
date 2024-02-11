#include <QPainter>
#include <QTimer>

#include "metadata.h"
#include "simulation_window.h"
#include "./ui_simulation_window.h"
#include "particle.h"

SimulationWindow::SimulationWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::SimulationWindow)
{
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
    int radius {5};

    physics::euler::Particle<physics::units::SI> particle {qtParticle::spawnParticle(point, radius)};
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
        QPoint point {qtParticle::toQPoint(particle)};
        qtParticle::Metadata data {std::any_cast<qtParticle::Metadata>(particle.metadata)};
        painter.drawEllipse(point, data.radius, data.radius); // center, width, height
    }
}

void SimulationWindow::stepSimulation()
{
    m_particles = physics::euler::step(m_particles, physics::units::time::milliseconds<double>(m_frameRate));
    update();
}
