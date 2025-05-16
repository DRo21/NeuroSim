#include "OpenGLWidget.h"
#include <algorithm>

/**
 * @brief Constructor for OpenGLWidget.
 * 
 * Sets default size and maximum number of voltage samples.
 */
OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent), maxSamples(100) {
    setMinimumSize(800, 600);
}

/**
 * @brief Initializes OpenGL rendering context and settings.
 */
void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Dark gray background
}

/**
 * @brief Adjusts the OpenGL viewport when the widget is resized.
 */
void OpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

/**
 * @brief Renders the voltage history as a 2D line graph.
 */
void OpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (voltageHistory.empty()) return;

    glColor3f(0.2f, 1.0f, 0.2f); // Green line
    glBegin(GL_LINE_STRIP);
    for (size_t i = 0; i < voltageHistory.size(); ++i) {
        float x = static_cast<float>(i) / (maxSamples - 1) * 2.0f - 1.0f;

        // Normalize voltage from [-80, 30] to [-1, 1]
        float normalized = (voltageHistory[i] + 80.0f) / 110.0f;
        float y = normalized * 2.0f - 1.0f;

        glVertex2f(x, y);
    }
    glEnd();
}

/**
 * @brief Adds a voltage value to the buffer and triggers a repaint.
 */
void OpenGLWidget::addVoltageSample(float voltage) {
    if (voltageHistory.size() >= maxSamples)
        voltageHistory.pop_front();
    voltageHistory.push_back(voltage);
    update();
}
