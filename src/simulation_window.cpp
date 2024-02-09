#include "simulation_window.h"
#include "./ui_simulation_window.h"

SimulationWindow::SimulationWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SimulationWindow)
{
    ui->setupUi(this);
}

SimulationWindow::~SimulationWindow()
{
    delete ui;
}
