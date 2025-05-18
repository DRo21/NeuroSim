#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>

/**
 * @class HeatmapWidget
 * @brief Custom OpenGL widget for rendering a 2D heatmap.
 *
 * Interprets a flat vector of floats (normalized in [0,1]) as a `width × height`
 * grid. Colors range from blue (0) to red (1). Renders each cell as a quad in OpenGL.
 */
class HeatmapWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    /**
     * @brief Constructs the HeatmapWidget.
     * @param parent Optional parent widget.
     */
    explicit HeatmapWidget(QWidget* parent = nullptr);

    /**
     * @brief Updates the internal heatmap data and requests a repaint.
     * @param data   Flattened vector of size `width * height`, values in [0,1].
     * @param width  Number of columns in the grid.
     * @param height Number of rows in the grid.
     */
    void setHeatmapData(const std::vector<float>& data, int width, int height);

protected:
    /**
     * @brief Initializes OpenGL functions and state.
     */
    void initializeGL() override;

    /**
     * @brief Handles viewport resize events.
     * @param w New widget width in pixels.
     * @param h New widget height in pixels.
     */
    void resizeGL(int w, int h) override;

    /**
     * @brief Renders the heatmap as colored quads.
     *
     * Iterates over the 2D grid. For each cell:
     *   - Retrieves normalized value in [0,1].
     *   - Maps it to (r,g,b) = (value, 0, 1−value).
     *   - Draws a quad spanning the appropriate OpenGL‐normalized coordinates.
     */
    void paintGL() override;

private:
    std::vector<float> m_data; ///< Flattened heatmap data (size = width * height).
    int m_width  = 0;          ///< Number of columns in the grid.
    int m_height = 0;          ///< Number of rows in the grid.
};
