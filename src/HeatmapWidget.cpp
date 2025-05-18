#include "HeatmapWidget.h"
#include <algorithm>

/**
 * @brief Constructs the HeatmapWidget.
 * @param parent Optional parent widget.
 */
HeatmapWidget::HeatmapWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{}

/**
 * @brief Updates internal data and triggers an OpenGL repaint.
 * @param data   Flattened grid of size width×height, each ∈ [0,1].
 * @param width  Number of columns for the grid.
 * @param height Number of rows for the grid.
 */
void HeatmapWidget::setHeatmapData(const std::vector<float>& data, int width, int height) {
    m_data   = data;
    m_width  = width;
    m_height = height;
    update();  // schedule a paintGL() call
}

/**
 * @brief Initializes OpenGL state (called once).
 *
 * Enables standard functions, sets clear color to black.
 */
void HeatmapWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

/**
 * @brief Adjusts the OpenGL viewport when the widget is resized.
 * @param w New width (pixels).
 * @param h New height (pixels).
 */
void HeatmapWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

/**
 * @brief Renders the heatmap by drawing colored quads for each cell.
 *
 * Each grid cell (x,y) is drawn as a quad in [-1,1] coordinates. The color is
 * calculated by mapping the data value ∈ [0,1] to (r=value, g=0, b=1-value).
 */
void HeatmapWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (m_data.empty() || m_width == 0 || m_height == 0) {
        return;
    }

    glBegin(GL_QUADS);
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            float value = std::clamp(m_data[y * m_width + x], 0.0f, 1.0f);
            float r = value;
            float g = 0.0f;
            float b = 1.0f - value;
            glColor3f(r, g, b);

            // Convert (x,y) cell to OpenGL coords in [-1,1]
            float x0 =  static_cast<float>(x)     / m_width  * 2.0f - 1.0f;
            float y0 =  static_cast<float>(y)     / m_height * 2.0f - 1.0f;
            float x1 = (static_cast<float>(x+1)  / m_width ) * 2.0f - 1.0f;
            float y1 = (static_cast<float>(y+1)  / m_height) * 2.0f - 1.0f;

            glVertex2f(x0, y0);
            glVertex2f(x1, y0);
            glVertex2f(x1, y1);
            glVertex2f(x0, y1);
        }
    }
    glEnd();
}
