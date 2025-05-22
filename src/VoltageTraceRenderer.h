/**
 * @file VoltageTraceRenderer.h
 * @brief Voltage trace renderer implementation for NeuroSim using QPainter lines.
 * @author Dario Romandini
 */

#pragma once

#include "ITraceRenderer.h"
#include <deque>
#include <QColor>

/**
 * @class VoltageTraceRenderer
 * @brief Implements a scrolling voltage trace renderer.
 *
 * Stores recent voltage samples in a circular buffer and renders them as a polyline.
 * Can be embedded in visualization widgets like OpenGLWidget.
 */
class VoltageTraceRenderer : public ITraceRenderer {
public:
    /**
     * @brief Constructor.
     * @param maxSamples Maximum number of samples to retain.
     * @param minV Minimum voltage (used for normalization).
     * @param maxV Maximum voltage (used for normalization).
     * @param color Color used to draw the trace line.
     */
    VoltageTraceRenderer(int maxSamples = 500,
                         float minV = -80.0f,
                         float maxV = 50.0f,
                         QColor color = Qt::green);

    /**
     * @brief Adds a new voltage sample to the buffer.
     * @param voltage Voltage value to add.
     */
    void addSample(float voltage);

    /**
     * @brief Clears all stored samples.
     */
    void clear();

    /**
     * @brief Renders the voltage trace into the provided rectangle.
     * @param painter QPainter context to draw with.
     * @param bounds Drawing bounds.
     */
    void render(QPainter& painter, const QRect& bounds) override;

private:
    std::deque<float> voltageSamples; ///< Circular buffer of voltage samples.
    int maxSamples;                   ///< Maximum buffer size.
    float minVoltage;                 ///< Voltage range minimum for scaling.
    float maxVoltage;                 ///< Voltage range maximum for scaling.
    QColor traceColor;                ///< Color of the polyline trace.
};
