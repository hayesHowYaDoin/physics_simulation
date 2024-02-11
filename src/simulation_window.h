#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include "physics_backend.hpp"
#include <QMainWindow>
#include <QMouseEvent>

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

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void stepSimulation();
    
    Ui::SimulationWindow *ui;
    std::vector<physics::euler::Particle<physics::units::SI>> m_particles;

    static constexpr int m_frameRate {33};  // Approximately 30fps
};
#endif // SIMULATIONWINDOW_H
