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
 * @brief Main GUI window integrating simulation controls and views.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void onStartSimulation();
    void onStopSimulation();
    void onGridSizeChanged(int nx, int ny);
    void onInputCurrentChanged(double current);
    void onDisplayModeChanged(int modeIndex);
    void onNeuronSelected(int neuronIndex);
    void onSimulationStep();

private:
    void setupUi();
    void connectSignals();

    ControlPanelWidget* controlPanel_;
    QSplitter*          viewSplitter_;
    HeatmapWidget*      heatmapView_;
    TraceViewWidget*    traceView_;
    RasterPlotWidget*   rasterView_;
    Simulation*         simulation_;
    QTimer*             simTimer_;
    double              currentInput_;
};

#endif // MAINWINDOW_H
