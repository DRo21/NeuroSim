/**
 * @file MainWindow.h
 * @brief Main GUI window for the NeuroSim application.
 * @author Dario Romandini
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ControlPanelWidget;
class HeatmapWidget;
class TraceViewWidget;
class RasterPlotWidget;
class Simulation;
class QSplitter;
class QTimer;

/**
 * @class MainWindow
 * @brief Integrates simulation logic with GUI widgets for visualization and control.
 *
 * Contains widgets for controlling the simulation and views for displaying neuron activity.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the main window.
     * @param parent Optional parent widget.
     */
    explicit MainWindow(QWidget* parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~MainWindow() override;

public slots:
    /** Starts the simulation timer. */
    void onStartSimulation();

    /** Stops the simulation timer. */
    void onStopSimulation();

private slots:
    /**
     * @brief Reinitializes the simulation with a new grid size.
     * @param nx Number of neurons along X-axis.
     * @param ny Number of neurons along Y-axis.
     */
    void onGridSizeChanged(int nx, int ny);

    /**
     * @brief Updates the input current for all neurons.
     * @param current Input current in nA.
     */
    void onInputCurrentChanged(double current);

    /**
     * @brief Updates the heatmap display mode.
     * @param modeIndex Index of the selected display mode.
     */
    void onDisplayModeChanged(int modeIndex);

    /**
     * @brief Sets the neuron index to monitor in the trace view.
     * @param neuronIndex Index of the neuron to visualize.
     */
    void onNeuronSelected(int neuronIndex);

    /** Executes one simulation step and updates all visualizations. */
    void onSimulationStep();

private:
    /** Initializes the layout and widgets. */
    void setupUi();

    /** Connects UI signals to MainWindow slots. */
    void connectSignals();

    ControlPanelWidget* controlPanel_;  ///< User control panel
    QSplitter*          viewSplitter_;  ///< Splits main visual views
    HeatmapWidget*      heatmapView_;   ///< Visualizes heatmap of neuron data
    TraceViewWidget*    traceView_;     ///< Displays voltage trace of selected neuron(s)
    RasterPlotWidget*   rasterView_;    ///< Displays spike raster plot
    Simulation*         simulation_;    ///< Underlying spiking neural network model
    QTimer*             simTimer_;      ///< Drives simulation steps
    double              currentInput_;  ///< Global external input current
};

#endif // MAINWINDOW_H
