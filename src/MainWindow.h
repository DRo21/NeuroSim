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
 * @brief Main application window for the NeuroSim simulator.
 *
 * Manages the UI components, simulation timing, and command input/output.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructs the MainWindow.
     * @param parent Optional parent widget.
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for MainWindow.
     */
    ~MainWindow();

private slots:
    /**
     * @brief Slot to update the simulation on timer tick.
     */
    void updateSimulation();

    /**
     * @brief Slot to handle user input commands.
     */
    void handleCommand();

private:
    /**
     * @brief Appends text to the command output log.
     * @param text Text to append.
     */
    void appendToLog(const QString& text);

    OpenGLWidget* openGLWidget;    ///< Widget rendering neuron activity graph.
    HeatmapWidget* heatmapWidget;  ///< Widget rendering heatmap visualization.
    Simulation simulation;         ///< Simulation engine instance.
    QTimer* simTimer;              ///< Timer controlling simulation updates.

    QPlainTextEdit* commandOutput; ///< Read-only log output area.
    QLineEdit* commandInput;       ///< Command input field.

    bool simulationRunning = false; ///< Flag for simulation state.
};
