#include "OpenGLWidget.h"
#include <QPainter>

/**
 * @brief Constructs the OpenGLWidget, reserving space in the deque.
 * @param parent Optional parent widget.
 */
OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    voltageSamples.clear();
}

/**
 * @brief Default destructor.
 */
OpenGLWidget::~OpenGLWidget() = default;

/**
 * @brief Adds a new voltage sample to the circular buffer and requests repaint.
 * @param voltage The new voltage value to append.
 */
void OpenGLWidget::addVoltageSample(float voltage) {
    if (voltageSamples.size() >= static_cast<size_t>(maxSamples)) {
        voltageSamples.pop_front();
    }
    voltageSamples.push_back(voltage);
    update();
}

/**
 * @brief Clears all stored voltage samples, effectively resetting the trace.
 */
void OpenGLWidget::clearVoltageTrace() {
    voltageSamples.clear();
    update();
}

/**
 * @brief One-time OpenGL initialization.
 */
void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

/**
 * @brief Adjusts OpenGL viewport whenever the widget is resized.
 * @param w New width in pixels.
 * @param h New height in pixels.
 */
void OpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

/**
 * @brief Renders the voltage trace by drawing a polyline of samples.
 *
 * - Clears the OpenGL buffer.
 * - Uses QPainter with anti-aliasing to draw a green line from left to right.
 * - Normalizes each voltage sample into [0,1], then maps to screen-Y in [0,h].
 */
void OpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::green);

    int w = width();
    int h = height();
    if (voltageSamples.empty()) {
        return;
    }

    const int sampleCount = static_cast<int>(voltageSamples.size());
    float xStep = static_cast<float>(w) / (maxSamples - 1);

    // Compute first point
    float firstVal = (voltageSamples.front() - minVoltage) / (maxVoltage - minVoltage);
    firstVal = std::clamp(firstVal, 0.0f, 1.0f);
    QPointF lastPoint(0.0f, h - firstVal * h);

    for (int i = 1; i < sampleCount; ++i) {
        float normalized = (voltageSamples[i] - minVoltage) / (maxVoltage - minVoltage);
        normalized = std::clamp(normalized, 0.0f, 1.0f);
        float x = i * xStep;
        float y = h - normalized * h;
        QPointF currentPoint(x, y);
        painter.drawLine(lastPoint, currentPoint);
        lastPoint = currentPoint;
    }
}
