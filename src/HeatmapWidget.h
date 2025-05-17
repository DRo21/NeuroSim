#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>

/**
 * @class HeatmapWidget
 * @brief Custom OpenGL widget to render a 2D heatmap visualization.
 *
 * Displays heatmap data as colored points scaled between blue and red.
 */
class HeatmapWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    /**
     * @brief Constructs the HeatmapWidget.
     * @param parent Optional parent widget.
     */
    explicit HeatmapWidget(QWidget *parent = nullptr);

    /**
     * @brief Sets the heatmap data and dimensions to render.
     * @param data Vector of heatmap values (normalized between 0 and 1).
     * @param width Width of heatmap grid.
     * @param height Height of heatmap grid.
     */
    void setHeatmapData(const std::vector<float>& data, int width, int height);

protected:
    /**
     * @brief Initializes OpenGL context and settings.
     */
    void initializeGL() override;

    /**
     * @brief Handles viewport resizing.
     * @param w New width.
     * @param h New height.
     */
    void resizeGL(int w, int h) override;

    /**
     * @brief Renders the heatmap visualization.
     */
    void paintGL() override;

private:
    std::vector<float> m_data; ///< Heatmap data buffer.
    int m_width = 0;           ///< Heatmap width.
    int m_height = 0;          ///< Heatmap height.
};
