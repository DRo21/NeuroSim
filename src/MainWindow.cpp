#include "MainWindow.h"
#include "ControlPanelWidget.h"
#include "HeatmapWidget.h"
#include "TraceViewWidget.h"
#include "RasterPlotWidget.h"
#include "Simulation.h"

#include <QVBoxLayout>
#include <QSplitter>
#include <QTimer>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      controlPanel_(new ControlPanelWidget(this)),
      viewSplitter_(new QSplitter(Qt::Horizontal, this)),
      heatmapView_(new HeatmapWidget(this)),
      traceView_(new TraceViewWidget(this)),
      rasterView_(new RasterPlotWidget(this)),
      simulation_(nullptr),
      simTimer_(new QTimer(this)),
      currentInput_(0.0)
{
    setupUi();
    connectSignals();
    onGridSizeChanged(10, 10);
}

MainWindow::~MainWindow()
{
    delete simulation_;
}

void MainWindow::setupUi()
{
    auto central = new QWidget(this);
    auto layout = new QVBoxLayout(central);
    layout->addWidget(controlPanel_);

    viewSplitter_->addWidget(heatmapView_);
    viewSplitter_->addWidget(traceView_);
    viewSplitter_->addWidget(rasterView_);
    viewSplitter_->setStretchFactor(0, 2);
    viewSplitter_->setStretchFactor(1, 1);
    viewSplitter_->setStretchFactor(2, 1);

    layout->addWidget(viewSplitter_);
    setCentralWidget(central);
    setWindowTitle(tr("NeuroSim – Spiking Neural Network Simulator"));
    resize(1400, 800);
}

void MainWindow::connectSignals()
{
    connect(controlPanel_, &ControlPanelWidget::startSimulation, this, &MainWindow::onStartSimulation);
    connect(controlPanel_, &ControlPanelWidget::stopSimulation, this, &MainWindow::onStopSimulation);
    connect(controlPanel_, &ControlPanelWidget::gridSizeChanged, this, &MainWindow::onGridSizeChanged);
    connect(controlPanel_, &ControlPanelWidget::inputCurrentChanged, this, &MainWindow::onInputCurrentChanged);
    connect(controlPanel_, &ControlPanelWidget::displayModeChanged, this, &MainWindow::onDisplayModeChanged);
    connect(controlPanel_, &ControlPanelWidget::neuronSelected, this, &MainWindow::onNeuronSelected);
    connect(simTimer_, &QTimer::timeout, this, &MainWindow::onSimulationStep);
}

void MainWindow::onStartSimulation()
{
    simTimer_->start(0);
}

void MainWindow::onStopSimulation()
{
    simTimer_->stop();
}

void MainWindow::onGridSizeChanged(int nx, int ny)
{
    delete simulation_;
    simulation_ = new Simulation(nx, ny);
    simulation_->setInputCurrent(currentInput_);

    heatmapView_->setSimulation(simulation_);
    traceView_->setSimulation(simulation_);
    rasterView_->setSimulation(simulation_);

    heatmapView_->updateView();
    traceView_->updateView();
    rasterView_->updateView();
}

void MainWindow::onInputCurrentChanged(double current)
{
    currentInput_ = current;
    if (simulation_)
        simulation_->setInputCurrent(current);
}

void MainWindow::onDisplayModeChanged(int modeIndex)
{
    heatmapView_->setDisplayMode(static_cast<HeatmapWidget::DisplayMode>(modeIndex));
}

void MainWindow::onNeuronSelected(int neuronIndex)
{
    traceView_->setNeuronIndex(neuronIndex);
    if (simulation_)
        simulation_->setSelectedNeuron(neuronIndex);
}

void MainWindow::onSimulationStep()
{
    if (simulation_) {
        simulation_->step();
        heatmapView_->updateView();
        traceView_->updateView();
        rasterView_->updateView();
    }
}
