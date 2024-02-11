#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

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
    Ui::SimulationWindow *ui;
    QVector<QPoint> m_points;
};
#endif // SIMULATIONWINDOW_H
