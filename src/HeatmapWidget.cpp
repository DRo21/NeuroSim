#include "HeatmapWidget.h"
#include <algorithm>
#include <cmath>

/**
 * @brief Constructs the HeatmapWidget.
 * @param parent Optional parent widget.
 */
HeatmapWidget::HeatmapWidget(QWidget *parent)
    : QOpenGLWidget(parent) {}

/**
 * @brief Sets the heatmap data and triggers repaint.
 * @param data Heatmap values.
 * @param width Heatmap grid width.
 * @param height Heatmap grid height.
 */
void HeatmapWidget::setHeatmapData(const std::vector<float>& data, int width, int height) {
    m_data = data;
    m_width = width;
    m_height = height;
    update();
}

/**
 * @brief Initializes OpenGL and sets background color.
 */
void HeatmapWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

/**
 * @brief Resizes the OpenGL viewport.
 * @param w New width.
 * @param h New height.
 */
void HeatmapWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

/**
 * @brief Paints the heatmap using OpenGL points with color mapped from data values.
 */
void HeatmapWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (m_data.empty() || m_width == 0 || m_height == 0) return;

    glBegin(GL_POINTS);
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            float value = m_data[y * m_width + x];
            // Map value [0..1] to color (blue -> red)
            float r = std::min(1.0f, value);
            float g = 0.0f;
            float b = 1.0f - r;
            glColor3f(r, g, b);
            glVertex2f(
                (float)x / (m_width - 1) * 2.0f - 1.0f,
                (float)y / (m_height - 1) * 2.0f - 1.0f
            );
        }
    }
    glEnd();
}
