#include "OpenGLWidget.h"
#include <QPainter>

/**
 * @brief Constructs the OpenGLWidget, initializing data buffers.
 * @param parent Optional parent widget.
 */
OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent) {
    voltageSamples.reserve(maxSamples);
}

/**
 * @brief Destructor.
 */
OpenGLWidget::~OpenGLWidget() = default;

/**
 * @brief Adds a voltage sample to the circular buffer.
 * @param voltage The new voltage sample value.
 */
void OpenGLWidget::addVoltageSample(float voltage) {
    if (voltageSamples.size() >= maxSamples) {
        voltageSamples.pop_front();
    }
    voltageSamples.push_back(voltage);
    update();  // Trigger repaint
}

/**
 * @brief OpenGL initialization.
 *
 * Sets up OpenGL functions and any necessary state.
 */
void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Black background
}

/**
 * @brief Handles widget resizing.
 * @param w Width in pixels.
 * @param h Height in pixels.
 */
void OpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

/**
 * @brief Paints the voltage trace line graph.
 *
 * Draws the voltage trace by mapping voltage samples to widget coordinates.
 */
void OpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::green);

    int width = this->width();
    int height = this->height();

    if (voltageSamples.isEmpty()) return;

    // Map voltage samples to points on the widget
    float xStep = static_cast<float>(width) / maxSamples;

    QPointF lastPoint(0, height - ((voltageSamples[0] - minVoltage) / (maxVoltage - minVoltage)) * height);

    for (int i = 1; i < voltageSamples.size(); ++i) {
        float x = i * xStep;
        float normalizedVoltage = (voltageSamples[i] - minVoltage) / (maxVoltage - minVoltage);
        float y = height - (normalizedVoltage * height);

        QPointF currentPoint(x, y);
        painter.drawLine(lastPoint, currentPoint);
        lastPoint = currentPoint;
    }
}
