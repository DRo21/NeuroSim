#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QPlainTextEdit>
#include <QLineEdit>
#include "OpenGLWidget.h"
#include "Simulation.h"

/**
 * @brief The MainWindow class for NeuroSim GUI.
 * 
 * This class manages the main user interface, command handling, and simulation timing.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructor for MainWindow.
     * @param parent Optional parent widget.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for MainWindow.
     */
    ~MainWindow();

private slots:
    /**
     * @brief Updates the simulation periodically.
     */
    void updateSimulation();

    /**
     * @brief Handles user command input.
     */
    void handleCommand();

private:
    /**
     * @brief Appends text to the command output field.
     * 
     * @param text The string to append.
     */
    void appendToLog(const QString& text);

    OpenGLWidget* openGLWidget;    ///< Widget for OpenGL-based neuron activity rendering.
    Simulation simulation;         ///< The simulation logic handler.
    QTimer* simTimer;              ///< Timer to trigger simulation updates.

    QPlainTextEdit* commandOutput; ///< Output field for logging messages.
    QLineEdit* commandInput;       ///< Input field for user commands.

    bool simulationRunning = false; ///< Flag indicating whether the simulation is running.
};
