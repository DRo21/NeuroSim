/**
 * @file TraceViewWidget.h
 * @brief Defines the TraceViewWidget for visualizing voltage traces over time.
 * @author Dario Romandini
 */

#ifndef TRACEVIEWWIDGET_H
#define TRACEVIEWWIDGET_H

#include <QWidget>
#include <vector>
#include <deque>
#include "Simulation.h"

/**
 * @class TraceViewWidget
 * @brief Widget for displaying membrane potential traces of one or more neurons.
 *
 * Displays voltage traces using a circular buffer, with support for individual neuron
 * selection, stacked display, cursor tracking, and live updates.
 */
class TraceViewWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the trace view widget.
     * @param parent Parent widget.
     */
    explicit TraceViewWidget(QWidget* parent = nullptr);

    /**
     * @brief Set the simulation whose neuron voltages will be displayed.
     * @param sim Pointer to the Simulation instance.
     */
    void setSimulation(Simulation* sim);

    /**
     * @brief Set the neuron index to display. If -1, shows all neurons stacked.
     * @param idx Index of the neuron or -1 for all.
     */
    void setNeuronIndex(int idx);

    /**
     * @brief Get the currently selected neuron index.
     * @return Selected neuron index.
     */
    int neuronIndex() const;

    /**
     * @brief Append voltage samples and trigger repaint.
     */
    void updateView();

protected:
    void paintEvent(QPaintEvent* ev) override;
    void mouseMoveEvent(QMouseEvent* ev) override;

private:
    Simulation* simulation_ = nullptr;  ///< Pointer to the simulation.
    int neuronIndex_ = -1;              ///< Selected neuron index (-1 = all).
    bool freeze_ = false;               ///< Freeze toggle (stops auto-refresh).
    QPoint cursorPos_;                  ///< Cursor for inspection.

    static constexpr double windowMs_ = 200.0;    ///< Trace window in ms.
    static constexpr int maxBufferSize_ = 500;    ///< Max samples to keep.

    std::vector<std::deque<double>> voltageBuffers_; ///< Voltage trace buffers.

    void drawTraces(QPainter& p);
    void drawCursorInfo(QPainter& p);
};

#endif // TRACEVIEWWIDGET_H
