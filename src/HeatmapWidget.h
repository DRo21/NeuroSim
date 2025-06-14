/**
 * @file HeatmapWidget.h
 * @brief Defines the HeatmapWidget for visualizing neuron values in a grid.
 * @author Dario Romandini
 */

#ifndef HEATMAPWIDGET_H
#define HEATMAPWIDGET_H

#include <QWidget>
#include "Simulation.h"

/**
 * @class HeatmapWidget
 * @brief Widget displaying a 2D heatmap of neuron values (voltage, spike rate, amplitude).
 */
class HeatmapWidget : public QWidget
{
    Q_OBJECT

public:
    enum DisplayMode { Voltage = 0, SpikeRate, Amplitude };

    explicit HeatmapWidget(QWidget* parent = nullptr);
    void setSimulation(Simulation* sim);
    void setDisplayMode(DisplayMode mode);
    DisplayMode displayMode() const;
    void updateView();

protected:
    void paintEvent(QPaintEvent* ev) override;
    void wheelEvent(QWheelEvent* ev) override;
    void mousePressEvent(QMouseEvent* ev) override;
    void mouseMoveEvent(QMouseEvent* ev) override;

private:
    Simulation* simulation_;
    DisplayMode mode_;
    double zoom_;
    QPoint panOffset_;
    bool selecting_;
    QRect selectionRect_;

    void drawHeatmap(QPainter& p);
    void drawSelection(QPainter& p);
    double computeValue(int idx) const;
};

#endif // HEATMAPWIDGET_H
