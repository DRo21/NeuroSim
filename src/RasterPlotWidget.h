// RasterPlotWidget.h
#ifndef RASTERPLOTWIDGET_H
#define RASTERPLOTWIDGET_H

#include <QWidget>
#include "Simulation.h"

/**
 * @brief Widget displaying a spike raster plot.
 *
 * X‐axis = time, Y‐axis = neuron index, one dot per spike.
 */
class RasterPlotWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructs the raster plot view.
     * @param parent Parent widget.
     */
    explicit RasterPlotWidget(QWidget* parent = nullptr);

    /**
     * @brief Attach a simulation to visualize.
     * @param sim Simulation pointer.
     */
    void setSimulation(Simulation* sim);

    /**
     * @brief Refresh and repaint the raster.
     */
    void updateView();

protected:
    void paintEvent(QPaintEvent* ev) override;

private:
    Simulation* simulation_;
};

#endif // RASTERPLOTWIDGET_H
