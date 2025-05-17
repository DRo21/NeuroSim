#include "MainWindow.h"
#include <QVBoxLayout>
#include <QSpacerItem>

/**
 * @brief Constructs the MainWindow UI and connects signals/slots.
 * 
 * Initializes UI elements, layouts, and simulation timer.
 * @param parent Optional parent widget.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), simulation(100 * 100) {

    setWindowTitle("NeuroSim - Neural Activity Simulator");
    resize(1200, 800);
    showMaximized();

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    openGLWidget = new OpenGLWidget(this);
    heatmapWidget = new HeatmapWidget(this);

    // Set minimum sizes for widgets to avoid shrinking too much
    openGLWidget->setMinimumSize(400, 400);
    heatmapWidget->setMinimumSize(400, 400);

    // Horizontal layout to hold two panels side-by-side
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(openGLWidget, 1);
    topLayout->addSpacing(20);  ///< Adds padding between the two panels
    topLayout->addWidget(heatmapWidget, 1);

    mainLayout->addLayout(topLayout);

    // Command output log (read-only)
    commandOutput = new QPlainTextEdit(this);
    commandOutput->setReadOnly(true);
    commandOutput->setMaximumHeight(150);
    mainLayout->addWidget(commandOutput);

    // Command input field
    commandInput = new QLineEdit(this);
    commandInput->setPlaceholderText("Enter command...");
    mainLayout->addWidget(commandInput);

    // Connect input field return key to command handler
    connect(commandInput, &QLineEdit::returnPressed, this, &MainWindow::handleCommand);

    // Timer for periodic simulation updates
    simTimer = new QTimer(this);
    connect(simTimer, &QTimer::timeout, this, &MainWindow::updateSimulation);

    simulationRunning = false;
}

/**
 * @brief Destructor for MainWindow.
 */
MainWindow::~MainWindow() {}

/**
 * @brief Updates the simulation and refreshes UI components.
 *
 * Steps the simulation forward, updates the voltage graph and heatmap.
 */
void MainWindow::updateSimulation() {
    if (!simulationRunning) return;

    simulation.step(0.1);

    // Update voltage plot from first neuron
    float voltage = simulation.neurons().at(0).getVoltage();
    openGLWidget->addVoltageSample(voltage);

    // Update heatmap using real neuron data
    const int heatmapWidth = 100;
    const int heatmapHeight = 100;
    std::vector<float> voltageGrid = simulation.getVoltageGrid(heatmapWidth, heatmapHeight);
    heatmapWidget->setHeatmapData(voltageGrid, heatmapWidth, heatmapHeight);
}

/**
 * @brief Parses and executes user commands entered in the input field.
 *
 * Supports commands such as start, stop, set current, status, and help.
 */
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
    } else if (cmd == "stop") {
        if (simulationRunning) {
            simulationRunning = false;
            simTimer->stop();
            appendToLog("Simulation stopped.");
        } else {
            appendToLog("Simulation already stopped.");
        }
    } else if (cmd.startsWith("set current ")) {
        bool ok = false;
        double val = cmd.mid(QString("set current ").length()).toDouble(&ok);
        if (ok) {
            simulation.setInputCurrent(val);
            appendToLog(QString("Input current set to %1").arg(val));
        } else {
            appendToLog("Invalid current value.");
        }
    } else if (cmd == "status") {
        QString status = QString("Simulation running: %1\nNeuron count: %2\nInput current: %3")
            .arg(simulationRunning ? "Yes" : "No")
            .arg(simulation.neurons().size())
            .arg(simulation.getInputCurrent());
        appendToLog(status);
    } else if (cmd == "help") {
        appendToLog("Available commands:\n"
                    "start - Start simulation\n"
                    "stop - Stop simulation\n"
                    "set current <value> - Set input current\n"
                    "status - Show simulation status\n"
                    "help - Show this help");
    } else {
        appendToLog("Unknown command. Type 'help' for list.");
    }
}

/**
 * @brief Appends text to the command output log window.
 * @param text The message to append.
 */
void MainWindow::appendToLog(const QString& text) {
    commandOutput->appendPlainText(text);
}
