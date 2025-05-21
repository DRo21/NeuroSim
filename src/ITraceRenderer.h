// ITraceRenderer.h
#pragma once
#include <QPainter>
#include <QRect>

/**
 * @interface ITraceRenderer
 * @brief Interface for trace rendering strategies in OpenGLWidget.
 *
 * Allows rendering of various types of trace visualizations using QPainter.
 * Facilitates Open-Closed Principle by decoupling OpenGLWidget from rendering logic.
 */
class ITraceRenderer {
public:
    virtual ~ITraceRenderer() = default;

    /**
     * @brief Render the trace using the provided QPainter and bounds.
     * @param painter QPainter to draw with.
     * @param bounds Rectangle defining the canvas area.
     */
    virtual void render(QPainter& painter, const QRect& bounds) = 0;
};

// VoltageTraceRenderer.h
#pragma once
#include "ITraceRenderer.h"
#include <deque>
#include <algorithm>

/**
 * @class VoltageTraceRenderer
 * @brief Implements voltage trace rendering for a single neuron.
 */
class VoltageTraceRenderer : public ITraceRenderer {
public:
    /**
     * @brief Adds a voltage sample to the circular buffer.
     * @param voltage Voltage value (e.g., in mV).
     */
    void addSample(float voltage);

    /**
     * @brief Clears all stored voltage samples.
     */
    void clear();

    /**
     * @brief Renders the voltage trace using a green polyline.
     * @param painter QPainter object.
     * @param bounds Drawing area.
     */
    void render(QPainter& painter, const QRect& bounds) override;

private:
    std::deque<float> voltageSamples; ///< Circular buffer of recent samples.
    const int maxSamples = 500;       ///< Maximum number of samples to keep.
    const float minVoltage = -80.0f;  ///< Minimum voltage value.
    const float maxVoltage = 50.0f;   ///< Maximum voltage value.
};
