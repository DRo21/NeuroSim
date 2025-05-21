#include "VoltageTraceRenderer.h"
#include <QPainter>
#include <algorithm>

/**
 * @brief Constructs the VoltageTraceRenderer.
 */
VoltageTraceRenderer::VoltageTraceRenderer(int maxSamples, float minV, float maxV, QColor color)
    : maxSamples(maxSamples), minVoltage(minV), maxVoltage(maxV), traceColor(color) {
    voltageSamples.clear();
}

/**
 * @brief Adds a new voltage value to the circular buffer.
 */
void VoltageTraceRenderer::addSample(float value) {
    if (voltageSamples.size() >= static_cast<size_t>(maxSamples)) {
        voltageSamples.pop_front();
    }
    voltageSamples.push_back(value);
}

/**
 * @brief Clears all stored voltage samples.
 */
void VoltageTraceRenderer::clear() {
    voltageSamples.clear();
}

/**
 * @brief Renders the voltage trace as a green polyline on the given painter.
 */
void VoltageTraceRenderer::render(QPainter* painter, int width, int height) {
    if (voltageSamples.empty()) return;

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(traceColor);

    const int sampleCount = static_cast<int>(voltageSamples.size());
    float xStep = static_cast<float>(width) / (maxSamples - 1);

    float firstNorm = (voltageSamples.front() - minVoltage) / (maxVoltage - minVoltage);
    firstNorm = std::clamp(firstNorm, 0.0f, 1.0f);
    QPointF lastPoint(0.0f, height - firstNorm * height);

    for (int i = 1; i < sampleCount; ++i) {
        float norm = (voltageSamples[i] - minVoltage) / (maxVoltage - minVoltage);
        norm = std::clamp(norm, 0.0f, 1.0f);
        QPointF currentPoint(i * xStep, height - norm * height);
        painter->drawLine(lastPoint, currentPoint);
        lastPoint = currentPoint;
    }

    painter->restore();
}
