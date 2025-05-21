#include "TraceViewWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPainterPath>
#include <algorithm>

TraceViewWidget::TraceViewWidget(QWidget* parent)
    : QWidget(parent)
{
    setMouseTracking(true);
}

void TraceViewWidget::setSimulation(Simulation* sim)
{
    simulation_ = sim;
    if (simulation_) {
        int N = simulation_->neuronCount();
        voltageBuffers_.assign(N, std::deque<double>());
    }
    updateView();
}

void TraceViewWidget::setNeuronIndex(int idx)
{
    neuronIndex_ = idx;
    updateView();
}

void TraceViewWidget::updateView()
{
    if (!simulation_) return;

    // Sample current voltage for each neuron and append to buffer
    int N = simulation_->neuronCount();
    for (int i = 0; i < N; ++i) {
        double v = simulation_->getNeuron(i)->getVoltage();
        auto& buf = voltageBuffers_[i];
        buf.push_back(v);
        if (static_cast<int>(buf.size()) > maxBufferSize_) {
            buf.pop_front();
        }
    }

    // Trigger repaint unless frozen
    if (!freeze_) {
        repaint();
    }
}

void TraceViewWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.fillRect(rect(), Qt::black);
    drawTraces(p);
    drawCursorInfo(p);
}

void TraceViewWidget::drawTraces(QPainter& p)
{
    if (!simulation_) return;

    int w = width();
    int h = height();
    int totalNeurons = (neuronIndex_ < 0 ? simulation_->neuronCount() : 1);
    double yStep = static_cast<double>(h) / totalNeurons;

    for (int n = 0; n < totalNeurons; ++n) {
        int idx = (neuronIndex_ < 0 ? n : neuronIndex_);
        const auto& buf = voltageBuffers_[idx];
        if (buf.empty()) continue;

        QPainterPath path;
        for (int i = 0; i < static_cast<int>(buf.size()); ++i) {
            double x = (static_cast<double>(i) / (maxBufferSize_-1)) * w;
            double normV = (buf[i] + 80.0) / 100.0;
            double y = (n + 1) * yStep - normV * yStep;
            if (i == 0) path.moveTo(x, y);
            else        path.lineTo(x, y);
        }
        p.setPen(QPen(Qt::green));
        p.drawPath(path);
    }
}

void TraceViewWidget::drawCursorInfo(QPainter& p)
{
    if (!simulation_) return;

    double tFraction = static_cast<double>(cursorPos_.x()) / width();
    double tMs = tFraction * windowMs_;

    int neuron = neuronIndex_;
    if (neuron < 0) {
        int total = simulation_->neuronCount();
        neuron = std::clamp(int(cursorPos_.y() / double(height()) * total), 0, total-1);
    }

    const auto& buf = voltageBuffers_[neuron];
    if (buf.empty()) return;
    int sampleIdx = std::clamp(int(tFraction * (buf.size()-1)), 0, int(buf.size()-1));
    double v = buf[sampleIdx];

    QString info = QString("t=%1 ms, n=%2, V=%3 mV")
                       .arg(tMs, 0, 'f', 1)
                       .arg(neuron)
                       .arg(v, 0, 'f', 1);

    p.setPen(Qt::white);
    p.drawText(cursorPos_ + QPoint(10, -10), info);
}

void TraceViewWidget::mouseMoveEvent(QMouseEvent* ev)
{
    cursorPos_ = ev->pos();
    if (!freeze_) {
        repaint();
    }
}
