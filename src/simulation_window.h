#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include "physics_backend.hpp"
#include <QMainWindow>
#include <QMouseEvent>

#include "particle.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SimulationWindow;
}
QT_END_NAMESPACE

class SimulationWindow : public QMainWindow
{
    Q_OBJECT

public:
    SimulationWindow(QWidget *parent = nullptr);
    ~SimulationWindow();

    SimulationWindow(const SimulationWindow&) = delete;
    SimulationWindow& operator=(const SimulationWindow&) = delete;

    SimulationWindow(SimulationWindow&&) = delete;
    SimulationWindow& operator=(SimulationWindow&&) = delete;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void stepSimulation();
    
    Ui::SimulationWindow *ui;
    std::vector<physics::euler::Particle<physics::units::SI>> m_particles;
    physics::usecases::Polygon2D<physics::units::SI::Length> m_constraint;

    static constexpr int m_frameRate {33};  // Approximately 30fps
    static constexpr std::pair<qtParticle::Pixels, qtParticle::Pixels> m_windowSize {800, 600};
};
#endif // SIMULATIONWINDOW_H
