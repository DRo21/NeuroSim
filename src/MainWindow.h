#pragma once

#include <QMainWindow>
#include <QTimer>
#include "OpenGLWidget.h"
#include "Simulation.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateSimulation();

private:
    OpenGLWidget* openGLWidget;
    Simulation simulation;
    QTimer* simTimer;
};
