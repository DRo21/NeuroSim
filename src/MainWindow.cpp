#include "MainWindow.h"
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

    commandOutput = new QPlainTextEdit(this);
    commandOutput->setReadOnly(true);
    commandOutput->setMaximumHeight(150);
    layout->addWidget(commandOutput);

    commandInput = new QLineEdit(this);
    commandInput->setPlaceholderText("Enter command...");
    layout->addWidget(commandInput);

    connect(commandInput, &QLineEdit::returnPressed, this, &MainWindow::handleCommand);

    simTimer = new QTimer(this);
    connect(simTimer, &QTimer::timeout, this, &MainWindow::updateSimulation);

    simulationRunning = false;
}

MainWindow::~MainWindow() {}

void MainWindow::updateSimulation() {
    if (!simulationRunning) return;

    simulation.step(0.1);

    float voltage = simulation.neurons().at(0).getVoltage();
    openGLWidget->addVoltageSample(voltage);
}

void MainWindow::handleCommand() {
    QString cmd = commandInput->text().trimmed();
    commandInput->clear();

    if (cmd == "start") {
        if (!simulationRunning) {
            simulationRunning = true;
            simTimer->start(100);
            appendToLog("Simulation started.");
        } else {
            appendToLog("Simulation already running.");
        }
    }
    else if (cmd == "stop") {
        if (simulationRunning) {
            simulationRunning = false;
            simTimer->stop();
            appendToLog("Simulation stopped.");
        } else {
            appendToLog("Simulation already stopped.");
        }
    }
    else if (cmd.startsWith("set current ")) {
        bool ok = false;
        double val = cmd.mid(QString("set current ").length()).toDouble(&ok);
        if (ok) {
            simulation.setInputCurrent(val);
            appendToLog(QString("Input current set to %1").arg(val));
        } else {
            appendToLog("Invalid current value.");
        }
    }
    else if (cmd == "status") {
        QString status = QString("Simulation running: %1\nNeuron count: %2\nInput current: %3")
            .arg(simulationRunning ? "Yes" : "No")
            .arg(simulation.neurons().size())
            .arg(simulation.getInputCurrent());
        appendToLog(status);
    }
    else if (cmd == "help") {
        appendToLog("Available commands:\n"
                    "start - Start simulation\n"
                    "stop - Stop simulation\n"
                    "set current <value> - Set input current\n"
                    "status - Show simulation status\n"
                    "help - Show this help");
    }
    else {
        appendToLog("Unknown command. Type 'help' for list.");
    }
}

void MainWindow::appendToLog(const QString& text) {
    commandOutput->appendPlainText(text);
}
