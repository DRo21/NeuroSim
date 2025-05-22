/**
 * @file VoltageTraceRenderer.cpp
 * @brief Implements VoltageTraceRenderer logic for visualizing voltage traces in NeuroSim.
 * @author Dario Romandini
 */

#include "VoltageTraceRenderer.h"
#include <QPainter>
#include <algorithm>

VoltageTraceRenderer::VoltageTraceRenderer(int maxSamples, float minV, float maxV, QColor color)
    : maxSamples(maxSamples), minVoltage(minV), maxVoltage(maxV), traceColor(color)
{
    voltageSamples.clear();
}

void VoltageTraceRenderer::addSample(float voltage)
{
    if (voltageSamples.size() >= static_cast<size_t>(maxSamples)) {
        voltageSamples.pop_front();
    }
    voltageSamples.push_back(voltage);
}

void VoltageTraceRenderer::clear()
{
    voltageSamples.clear();
}

void VoltageTraceRenderer::render(QPainter& painter, const QRect& bounds)
{
    if (voltageSamples.empty()) return;

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(traceColor);

    int w = bounds.width();
    int h = bounds.height();
    float xStep = static_cast<float>(w) / (maxSamples - 1);

    float firstNorm = std::clamp((voltageSamples.front() - minVoltage) / (maxVoltage - minVoltage), 0.0f, 1.0f);
    QPointF lastPoint(0.0f, h - firstNorm * h);

    for (size_t i = 1; i < voltageSamples.size(); ++i) {
        float norm = std::clamp((voltageSamples[i] - minVoltage) / (maxVoltage - minVoltage), 0.0f, 1.0f);
        QPointF currentPoint(i * xStep, h - norm * h);
        painter.drawLine(lastPoint, currentPoint);
        lastPoint = currentPoint;
    }
}
