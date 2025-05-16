#include "MainWindow.h"
#include <QTimer>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), simulation(1) {

    setWindowTitle("NeuroSim - Neural Activity Simulator");
    resize(800, 600);
    showFullScreen();

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    openGLWidget = new OpenGLWidget(this);
    layout->addWidget(openGLWidget);

    simTimer = new QTimer(this);
    connect(simTimer, &QTimer::timeout, this, &MainWindow::updateSimulation);
    simTimer->start(100);
}

MainWindow::~MainWindow() {}

void MainWindow::updateSimulation() {
    simulation.step(0.1);

    float voltage = simulation.neurons().at(0).getVoltage();
    openGLWidget->addVoltageSample(voltage);
}

