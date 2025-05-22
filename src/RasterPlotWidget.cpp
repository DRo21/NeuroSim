/**
 * @file RasterPlotWidget.cpp
 * @brief Implementation of RasterPlotWidget for spike time visualization in a raster format.
 * @author Dario Romandini
 */

#include "RasterPlotWidget.h"
#include <QPainter>

RasterPlotWidget::RasterPlotWidget(QWidget* parent)
    : QWidget(parent), simulation_(nullptr)
{
    setMinimumSize(200, 200);
}

void RasterPlotWidget::setSimulation(Simulation* sim)
{
    simulation_ = sim;
    updateView();
}

void RasterPlotWidget::updateView()
{
    repaint();
}

void RasterPlotWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.fillRect(rect(), Qt::black);

    if (!simulation_) return;

    const auto& events = simulation_->spikeEvents();
    double t1 = simulation_->currentTime();
    double t0 = std::max(0.0, t1 - 200.0);  // Show 200 ms window
    int w = width(), h = height();
    int N = simulation_->neuronCount();

    if (N == 0 || t1 <= t0) return;

    p.setPen(QPen(Qt::white, 1));
    for (const auto& ev : events) {
        double t = ev.first;
        int idx = ev.second;
        if (t < t0 || t > t1) continue;
        double x = (t - t0) / (t1 - t0) * w;
        double y = (idx + 0.5) / N * h;
        p.drawPoint(QPointF(x, y));
    }
}
