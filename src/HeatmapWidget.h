#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>

/**
 * @class HeatmapWidget
 * @brief Custom OpenGL widget for rendering a 2D heatmap visualization.
 *
 * Displays a heatmap based on a grid of float values normalized between 0 and 1.
 * Colors map from blue (low) to red (high).
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
     * @brief Sets the heatmap data and triggers a repaint.
     * @param data Vector of heatmap values normalized to [0,1].
     * @param width Number of columns in the heatmap grid.
     * @param height Number of rows in the heatmap grid.
     */
    void setHeatmapData(const std::vector<float>& data, int width, int height);

protected:
    /**
     * @brief Initializes OpenGL context and state.
     */
    void initializeGL() override;

    /**
     * @brief Handles resizing of the OpenGL viewport.
     * @param w New width in pixels.
     * @param h New height in pixels.
     */
    void resizeGL(int w, int h) override;

    /**
     * @brief Renders the heatmap visualization.
     */
    void paintGL() override;

private:
    std::vector<float> m_data; ///< Heatmap data stored in row-major order.
    int m_width = 0;           ///< Width of heatmap grid.
    int m_height = 0;          ///< Height of heatmap grid.
};
