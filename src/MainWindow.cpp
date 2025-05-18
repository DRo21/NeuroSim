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
      simulation(Constants::NeuronCount),
      selectedNeuron(0)  // Default selected neuron index
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

    // Top layout: side-by-side panels for trace and heatmap
    QHBoxLayout* topLayout = new QHBoxLayout();
    topLayout->addWidget(openGLWidget, 1);
    topLayout->addSpacing(20);  ///< Padding between panels
    topLayout->addWidget(heatmapWidget, 1);
    mainLayout->addLayout(topLayout);

    // Below: command output log (read-only) then input field
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
 * - Extracts the voltage of the currently selected neuron and appends it to the voltage trace.
 * - Calls Simulation::getVoltageGrid(...) to produce a 3×3 grid of normalized voltages.
 * - Updates the HeatmapWidget with that 3×3 data.
 */
void MainWindow::updateSimulation() {
    if (!simulationRunning) {
        return;
    }

    // Step the simulation by one time step
    simulation.step(Constants::SimulationTimeStep);

    // Plot the voltage of the selected neuron in the trace panel
    if (selectedNeuron >= 0 && selectedNeuron < simulation.neurons().size()) {
        float voltage = static_cast<float>(simulation.neurons().at(selectedNeuron).getVoltage());
        openGLWidget->addVoltageSample(voltage);
    } else {
        // Invalid index fallback (optional)
        appendToLog(QString("Warning: selected neuron index %1 out of range.").arg(selectedNeuron));
    }

    // Generate and display a 3×3 heatmap
    static const int heatmapWidth  = Constants::HeatmapRenderWidth;
    static const int heatmapHeight = Constants::HeatmapRenderHeight;
    std::vector<float> voltageGrid = simulation.getVoltageGrid(heatmapWidth, heatmapHeight);
    heatmapWidget->setHeatmapData(voltageGrid, heatmapWidth, heatmapHeight);
}

/**
 * @brief Processes a user-entered command from the input field.
 *
 * Supported commands:
 *   - "start"               : starts the simulation loop
 *   - "stop"                : stops the simulation loop
 *   - "set current <value>" : sets input current (overrides default)
 *   - "select neuron <index>" : selects neuron index for voltage trace display
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
    else if (cmd.startsWith("select neuron ")) {
        bool ok = false;
        int idx = cmd.mid(QString("select neuron ").length()).toInt(&ok);
        if (ok && idx >= 0 && idx < simulation.neurons().size()) {
            selectedNeuron = idx;

            // Clear the voltage trace immediately on neuron switch
            openGLWidget->clearVoltageTrace();

            // Immediately add current voltage sample of new neuron
            float voltage = static_cast<float>(simulation.neurons().at(selectedNeuron).getVoltage());
            openGLWidget->addVoltageSample(voltage);

            appendToLog(QString("Selected neuron %1 for voltage trace.").arg(idx));
        } else {
            appendToLog("Invalid neuron index.");
        }
    }
    else if (cmd == "status") {
        QString status = QString(
            "Simulation running: %1\n"
            "Neuron count: %2\n"
            "Input current: %3\n"
            "Selected neuron: %4"
        ).arg(simulationRunning ? "Yes" : "No")
         .arg(simulation.neurons().size())
         .arg(simulation.getInputCurrent())
         .arg(selectedNeuron);
        appendToLog(status);
    }
    else if (cmd == "help") {
        appendToLog(
            "Available commands:\n"
            "  start               - Start the simulation\n"
            "  stop                - Stop the simulation\n"
            "  set current <value> - Set input current\n"
            "  select neuron <idx> - Select neuron (0-based) for voltage trace\n"
            "  status              - Show simulation status\n"
            "  help                - Show this help"
        );
    }
    else {
        appendToLog("Unknown command. Type 'help' for a list of commands.");
    }
}

/**
 * @brief Appends a message line to the command output log (read-only).
 * @param text The message text to append.
 */
void MainWindow::appendToLog(const QString& text) {
    commandOutput->appendPlainText(text);
}
