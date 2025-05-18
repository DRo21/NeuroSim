#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QHBoxLayout>
#include "OpenGLWidget.h"
#include "HeatmapWidget.h"
#include "Simulation.h"
#include "Constants.h"

/**
 * @class MainWindow
 * @brief Main application window for the NeuroSim neural activity simulator.
 *
 * Manages the UI components, simulation timer, and command input/output.
 * Displays a voltage trace (left) and a heatmap of all neurons (right),
 * plus a console-style command input at the bottom.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructs the MainWindow UI.
     * @param parent Optional parent widget.
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for MainWindow.
     */
    ~MainWindow();

private slots:
    /**
     * @brief Timer slot that advances simulation and updates UI.
     *
     * - Calls Simulation::step(Constants::SimulationTimeStep)
     * - Updates the voltage trace from the selected neuron (index 0 by default)
     * - Regenerates and displays a small 3×3 heatmap of all neurons
     */
    void updateSimulation();

    /**
     * @brief Processes a command string entered by the user.
     *
     * Supported commands:
     *   - start                  : starts the simulation loop
     *   - stop                   : stops the simulation loop
     *   - set current <value>    : sets the input current for all neurons
     *   - select neuron <index>  : selects neuron for voltage trace
     *   - status                 : prints current simulation state
     *   - help                   : shows list of available commands
     */
    void handleCommand();

private:
    /**
     * @brief Appends a line of text to the command output log (read-only widget).
     * @param text The message to append.
     */
    void appendToLog(const QString& text);

    OpenGLWidget* openGLWidget;    ///< Widget for rendering a single-neuron voltage trace.
    HeatmapWidget* heatmapWidget;  ///< Widget for rendering the 3×3 heatmap.
    Simulation simulation;         ///< Simulation engine (manages all neurons).
    QTimer* simTimer;              ///< Timer that fires every SimulationIntervalMs.
    QPlainTextEdit* commandOutput; ///< Read-only text area for log messages.
    QLineEdit* commandInput;       ///< Single-line input field for commands.
    bool simulationRunning = false;///< Flag indicating whether the simulation is active.

    int selectedNeuron;            ///< Currently selected neuron index for voltage trace display.
};
