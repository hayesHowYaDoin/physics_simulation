#include <QPainter>
#include <QTimer>

#include "simulation_window.h"
#include "./ui_simulation_window.h"

SimulationWindow::SimulationWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::SimulationWindow),
    m_particles {QVector<ParticleObject>()}
{
    ui->setupUi(this);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&SimulationWindow::update));
    timer->start(1000);
}

SimulationWindow::~SimulationWindow()
{
    delete ui;
}

void SimulationWindow::mousePressEvent(QMouseEvent *event)
{
    ParticleObject particle(event->pos(), 5);
    m_particles.append(particle);
    update();
}

void SimulationWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));

    for (auto const& particle : m_particles)
    {
        painter.drawEllipse(particle.getPosition(), particle.getRadius(), particle.getRadius()); // center, width, height
    }
}
