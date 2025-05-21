#ifndef TRACEVIEWWIDGET_H
#define TRACEVIEWWIDGET_H

#include <QWidget>
#include <vector>
#include <deque>
#include "Simulation.h"

/**
 * @brief Widget for displaying membrane‐potential traces.
 *
 * Supports multiple neurons (overlay or stacked), a fixed
 * 200 ms window buffer, freeze/scroll, and cursor inspection.
 */
class TraceViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TraceViewWidget(QWidget* parent = nullptr);

    void setSimulation(Simulation* sim);
    void setNeuronIndex(int idx);
    void updateView();

protected:
    void paintEvent(QPaintEvent* ev) override;
    void mouseMoveEvent(QMouseEvent* ev) override;

private:
    Simulation*                      simulation_    = nullptr;
    int                              neuronIndex_   = -1;
    bool                             freeze_        = false;
    QPoint                           cursorPos_;

    static constexpr double          windowMs_      = 200.0;
    static constexpr int             maxBufferSize_ = 500;
    std::vector<std::deque<double>>  voltageBuffers_;

    void drawTraces(QPainter& p);
    void drawCursorInfo(QPainter& p);
};

#endif // TRACEVIEWWIDGET_H
