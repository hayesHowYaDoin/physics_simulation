#include <QPainter>

#include "simulation_window.h"
#include "./ui_simulation_window.h"

SimulationWindow::SimulationWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::SimulationWindow),
    m_points {QVector<QPoint>()}
{
    ui->setupUi(this);
}

SimulationWindow::~SimulationWindow()
{
    delete ui;
}

void SimulationWindow::mousePressEvent(QMouseEvent *event)
{
    m_points.append(event->pos());
    update();
}

void SimulationWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));

    for (const auto &point : m_points)
    {
        painter.drawEllipse(point, 50, 50); // center, width, height
    }
}
