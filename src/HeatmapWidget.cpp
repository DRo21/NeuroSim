/**
 * @file HeatmapWidget.cpp
 * @brief Implements the HeatmapWidget for visualizing neuron activity as a 2D heatmap.
 * @author Dario Romandini
 */

#include "HeatmapWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QSizePolicy>
#include <algorithm>
#include <cmath>

HeatmapWidget::HeatmapWidget(QWidget* parent)
    : QWidget(parent),
      simulation_(nullptr),
      mode_(Voltage),
      zoom_(1.5),
      panOffset_(0, 0),
      selecting_(false)
{
    setMinimumSize(300, 300);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void HeatmapWidget::setSimulation(Simulation* sim)
{
    simulation_ = sim;
    updateView();
}

void HeatmapWidget::setDisplayMode(DisplayMode mode)
{
    mode_ = mode;
    updateView();
}

HeatmapWidget::DisplayMode HeatmapWidget::displayMode() const
{
    return mode_;
}

void HeatmapWidget::updateView()
{
    update();
}

void HeatmapWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    drawHeatmap(painter);

    if (selecting_ || !selectionRect_.isNull())
        drawSelection(painter);
}

void HeatmapWidget::drawHeatmap(QPainter& p)
{
    if (!simulation_) return;

    int nx = simulation_->nx();
    int ny = simulation_->ny();
    int N = simulation_->neuronCount();
    QSize sz = size();
    double cellW = sz.width() * zoom_ / nx;
    double cellH = sz.height() * zoom_ / ny;

    std::vector<double> vals(N);
    for (int i = 0; i < N; ++i) {
        vals[i] = computeValue(i);
    }

    double minV, maxV;
    switch (mode_) {
        case Voltage:
            minV = -80.0;
            maxV = 40.0;
            break;
        case SpikeRate:
            minV = 0.0;
            maxV = 200.0;
            break;
        case Amplitude:
            minV = -80.0;
            maxV = 40.0;
            break;
    }

    for (int y = 0; y < ny; ++y) {
        for (int x = 0; x < nx; ++x) {
            int idx = y * nx + x;
            double norm = (vals[idx] - minV) / (maxV - minV);
            norm = std::clamp(norm, 0.0, 1.0);
            QColor col = QColor::fromHslF((1.0 - norm) * 0.75, 1.0, 0.5);
            QRectF cell(x * cellW, y * cellH, cellW, cellH);
            p.fillRect(cell.translated(panOffset_), col);
        }
    }
}

double HeatmapWidget::computeValue(int idx) const
{
    if (!simulation_) return 0.0;

    switch (mode_) {
        case Voltage:    return simulation_->getNeuron(idx)->getVoltage();
        case SpikeRate:  return simulation_->getSpikeRate(idx, 100);
        case Amplitude:  return simulation_->getSpikeAmplitude(idx, 100);
    }
    return 0.0;
}

void HeatmapWidget::drawSelection(QPainter& p)
{
    QPen pen(Qt::DashLine);
    pen.setWidth(2);
    p.setPen(pen);
    p.drawRect(selectionRect_);
}

void HeatmapWidget::wheelEvent(QWheelEvent* ev)
{
    zoom_ *= std::pow(1.001, ev->angleDelta().y());
    updateView();
}

void HeatmapWidget::mousePressEvent(QMouseEvent* ev)
{
    if (ev->buttons() & Qt::LeftButton) {
        selecting_ = true;
        selectionRect_.setTopLeft(ev->pos());
        selectionRect_.setBottomRight(ev->pos());
    } else if (ev->buttons() & Qt::RightButton) {
        panOffset_ += ev->pos();
    }
}

void HeatmapWidget::mouseMoveEvent(QMouseEvent* ev)
{
    if (selecting_) {
        selectionRect_.setBottomRight(ev->pos());
        update();
    }
}
