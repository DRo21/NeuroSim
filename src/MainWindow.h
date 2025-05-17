#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QHBoxLayout>
#include "OpenGLWidget.h"
#include "HeatmapWidget.h"
#include "Simulation.h"

/**
 * @class MainWindow
 * @brief Main application window for the NeuroSim neural activity simulator.
 *
 * Manages the UI components, simulation timer, and command input/output.
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
     * @brief Timer slot that updates the simulation step and UI.
     *
     * Advances simulation by one step, updates voltage plot and heatmap.
     */
    void updateSimulation();

    /**
     * @brief Handles commands entered by the user.
     *
     * Supports commands like start, stop, set current, status, and help.
     */
    void handleCommand();

private:
    /**
     * @brief Appends text to the command output log.
     * @param text Message string to append.
     */
    void appendToLog(const QString& text);

    OpenGLWidget* openGLWidget;    ///< Widget showing the voltage trace graph.
    HeatmapWidget* heatmapWidget;  ///< Widget showing the neuron heatmap.

    Simulation simulation;         ///< Simulation engine instance.

    QTimer* simTimer;              ///< Timer controlling simulation updates.

    QPlainTextEdit* commandOutput; ///< Read-only text area for command output.
    QLineEdit* commandInput;       ///< Input field for user commands.

    bool simulationRunning = false; ///< Flag to indicate if simulation is running.
};
