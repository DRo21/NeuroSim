/**
 * @file RasterPlotWidget.h
 * @brief Raster plot widget for visualizing spike events over time.
 * @author Dario Romandini
 */

#ifndef RASTERPLOTWIDGET_H
#define RASTERPLOTWIDGET_H

#include <QWidget>
#include "Simulation.h"

/**
 * @class RasterPlotWidget
 * @brief Displays a raster plot of neuron spikes over time.
 */
class RasterPlotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RasterPlotWidget(QWidget* parent = nullptr);
    void setSimulation(Simulation* sim);
    void updateView();

protected:
    void paintEvent(QPaintEvent* ev) override;

private:
    Simulation* simulation_;
};

#endif // RASTERPLOTWIDGET_H
