#include "VoltageTraceRenderer.h"

void VoltageTraceRenderer::addSample(float voltage) {
    if (voltageSamples.size() >= static_cast<size_t>(maxSamples)) {
        voltageSamples.pop_front();
    }
    voltageSamples.push_back(voltage);
}

void VoltageTraceRenderer::clear() {
    voltageSamples.clear();
}

void VoltageTraceRenderer::render(QPainter& painter, const QRect& bounds) {
    if (voltageSamples.empty()) return;

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::green);

    int w = bounds.width();
    int h = bounds.height();
    float xStep = static_cast<float>(w) / (maxSamples - 1);

    float firstVal = std::clamp((voltageSamples.front() - minVoltage) / (maxVoltage - minVoltage), 0.0f, 1.0f);
    QPointF lastPoint(0.0f, h - firstVal * h);

    for (size_t i = 1; i < voltageSamples.size(); ++i) {
        float norm = std::clamp((voltageSamples[i] - minVoltage) / (maxVoltage - minVoltage), 0.0f, 1.0f);
        QPointF currentPoint(i * xStep, h - norm * h);
        painter.drawLine(lastPoint, currentPoint);
        lastPoint = currentPoint;
    }
}