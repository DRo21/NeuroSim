#include "MainWindow.h"
#include "Constants.h" 
#include <QVBoxLayout>

/**
 * @brief Constructs the MainWindow UI and connects signals/slots.
 *
 * Initializes the OpenGLWidget (voltage trace), HeatmapWidget (3×3 grid),
 * and the command console. Does not start the simulation by default.
 *
 * @param parent Optional parent widget.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      simulation(Constants::NeuronCount)   // Create Simulation with 3×3 = 9 neurons
{
    setWindowTitle("NeuroSim - Neural Activity Simulator");
    resize(1200, 800);
    showMaximized();

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Create and configure the two main panels:
    openGLWidget = new OpenGLWidget(this);
    heatmapWidget = new HeatmapWidget(this);

    openGLWidget->setMinimumSize(400, 400);
    heatmapWidget->setMinimumSize(400, 400);

    // Top layout: side‐by‐side panels for trace and heatmap
    QHBoxLayout* topLayout = new QHBoxLayout();
    topLayout->addWidget(openGLWidget, 1);
    topLayout->addSpacing(20);  ///< Padding between panels
    topLayout->addWidget(heatmapWidget, 1);
    mainLayout->addLayout(topLayout);

    // Below: command output log (read‐only) then input field
    commandOutput = new QPlainTextEdit(this);
    commandOutput->setReadOnly(true);
    commandOutput->setMaximumHeight(150);
    mainLayout->addWidget(commandOutput);

    commandInput = new QLineEdit(this);
    commandInput->setPlaceholderText("Enter command...");
    mainLayout->addWidget(commandInput);
    connect(commandInput, &QLineEdit::returnPressed, this, &MainWindow::handleCommand);

    // Simulation timer (does not start until user types “start”)
    simTimer = new QTimer(this);
    connect(simTimer, &QTimer::timeout, this, &MainWindow::updateSimulation);

    // Initially, simulation is paused
    simulationRunning = false;
}

/**
 * @brief Destructor for MainWindow.
 */
MainWindow::~MainWindow() {}

/**
 * @brief Advances the simulation and updates both OpenGL panels.
 *
 * - Calls Simulation::step(Constants::SimulationTimeStep).
 * - Extracts the voltage of the first neuron (index 0) and appends it to the voltage trace.
 * - Calls Simulation::getVoltageGrid(3, 3) to produce a 3×3 grid of normalized voltages.
 * - Updates the HeatmapWidget with that 3×3 data.
 */
void MainWindow::updateSimulation() {
    if (!simulationRunning) {
        return;
    }

    // 1) Step the simulation by one time step
    simulation.step(Constants::SimulationTimeStep);

    // 2) Plot the voltage of the first neuron in the trace panel
    float voltage = static_cast<float>(simulation.neurons().at(0).getVoltage());
    openGLWidget->addVoltageSample(voltage);

    // 3) Generate and display a 3×3 heatmap
    static const int heatmapWidth  = Constants::HeatmapRenderWidth;
    static const int heatmapHeight = Constants::HeatmapRenderHeight;
    std::vector<float> voltageGrid = simulation.getVoltageGrid(heatmapWidth, heatmapHeight);
    heatmapWidget->setHeatmapData(voltageGrid, heatmapWidth, heatmapHeight);
}

/**
 * @brief Processes a user‐entered command from the input field.
 *
 * Supported commands:
 *   - "start"               : starts the simulation loop
 *   - "stop"                : stops the simulation loop
 *   - "set current <value>" : sets input current (overrides default)
 *   - "status"              : prints current state to the log
 *   - "help"                : lists available commands
 */
void MainWindow::handleCommand() {
    QString cmd = commandInput->text().trimmed();
    commandInput->clear();

    if (cmd == "start") {
        if (!simulationRunning) {
            simulationRunning = true;
            simTimer->start(Constants::SimulationIntervalMs);
            appendToLog("Simulation started.");
        } else {
            appendToLog("Simulation is already running.");
        }
    }
    else if (cmd == "stop") {
        if (simulationRunning) {
            simulationRunning = false;
            simTimer->stop();
            appendToLog("Simulation stopped.");
        } else {
            appendToLog("Simulation is already stopped.");
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
        QString status = QString(
            "Simulation running: %1\n"
            "Neuron count: %2\n"
            "Input current: %3"
        ).arg(simulationRunning ? "Yes" : "No")
         .arg(simulation.neurons().size())
         .arg(simulation.getInputCurrent());
        appendToLog(status);
    }
    else if (cmd == "help") {
        appendToLog(
            "Available commands:\n"
            "  start               - Start the simulation\n"
            "  stop                - Stop the simulation\n"
            "  set current <value> - Set input current\n"
            "  status              - Show simulation status\n"
            "  help                - Show this help"
        );
    }
    else {
        appendToLog("Unknown command. Type 'help' for a list of commands.");
    }
}

/**
 * @brief Appends a message line to the command output log (read‐only).
 * @param text The message text to append.
 */
void MainWindow::appendToLog(const QString& text) {
    commandOutput->appendPlainText(text);
}
