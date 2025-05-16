#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QPlainTextEdit>
#include <QLineEdit>
#include "OpenGLWidget.h"
#include "Simulation.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateSimulation();
    void handleCommand();

private:
    void appendToLog(const QString& text);

    OpenGLWidget* openGLWidget;
    Simulation simulation;
    QTimer* simTimer;

    QPlainTextEdit* commandOutput;
    QLineEdit* commandInput;

    bool simulationRunning = false;
};
