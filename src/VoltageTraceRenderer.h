#pragma once

#include "ITraceRenderer.h"
#include <deque>
#include <QColor>

/**
 * @class VoltageTraceRenderer
 * @brief Implements a scrolling voltage trace renderer.
 *
 * Stores recent voltage samples in a circular buffer and renders them as a continuous line.
 */
class VoltageTraceRenderer : public ITraceRenderer {
public:
    /**
     * @brief Constructor.
     * @param maxSamples Maximum number of samples to retain for drawing.
     * @param minV Minimum voltage value (used for normalization).
     * @param maxV Maximum voltage value (used for normalization).
     * @param color Color of the voltage trace.
     */
    VoltageTraceRenderer(int maxSamples = 500, float minV = -80.0f, float maxV = 50.0f, QColor color = Qt::green);

    /**
     * @brief Adds a voltage sample to the trace.
     * @param value The new voltage value to add.
     */
    void addSample(float value) override;

    /**
     * @brief Clears all stored samples.
     */
    void clear() override;

    /**
     * @brief Renders the voltage trace using the given painter.
     * @param painter QPainter context to draw into.
     * @param width Width of the drawing area in pixels.
     * @param height Height of the drawing area in pixels.
     */
    void render(QPainter* painter, int width, int height) override;

private:
    std::deque<float> voltageSamples; ///< Circular buffer of voltage values.
    int maxSamples;                   ///< Maximum number of samples retained.
    float minVoltage;                 ///< Minimum expected voltage (for normalization).
    float maxVoltage;                 ///< Maximum expected voltage (for normalization).
    QColor traceColor;                ///< Color used for the trace line.
};
