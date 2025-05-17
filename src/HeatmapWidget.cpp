#include "HeatmapWidget.h"
#include <algorithm>

/**
 * @brief Constructs the HeatmapWidget.
 * @param parent Optional parent widget.
 */
HeatmapWidget::HeatmapWidget(QWidget* parent)
    : QOpenGLWidget(parent) {}

/**
 * @brief Sets heatmap data and size, then triggers repaint.
 * @param data Heatmap values normalized to [0,1].
 * @param width Heatmap grid width.
 * @param height Heatmap grid height.
 */
void HeatmapWidget::setHeatmapData(const std::vector<float>& data, int width, int height) {
    m_data = data;
    m_width = width;
    m_height = height;
    update();  // Request repaint
}

/**
 * @brief Initializes OpenGL state.
 */
void HeatmapWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);  // Black background
}

/**
 * @brief Adjusts viewport to new size.
 * @param w New width.
 * @param h New height.
 */
void HeatmapWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

/**
 * @brief Renders the heatmap using colored points.
 *
 * Maps each heatmap value to a color between blue and red and draws
 * them as points scaled to the widget area.
 */
void HeatmapWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (m_data.empty() || m_width == 0 || m_height == 0) return;

    glBegin(GL_POINTS);

    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            float value = m_data[y * m_width + x];

            // Clamp value to [0, 1]
            value = std::clamp(value, 0.0f, 1.0f);

            // Color interpolation from blue (low) to red (high)
            float r = value;
            float g = 0.0f;
            float b = 1.0f - value;

            glColor3f(r, g, b);

            // Map grid coords [0, width/height] to OpenGL coords [-1, 1]
            float glX = static_cast<float>(x) / (m_width - 1) * 2.0f - 1.0f;
            float glY = static_cast<float>(y) / (m_height - 1) * 2.0f - 1.0f;

            glVertex2f(glX, glY);
        }
    }

    glEnd();
}
