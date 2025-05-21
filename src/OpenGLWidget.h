#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <memory>
#include "ITraceRenderer.h"

/**
 * @class OpenGLWidget
 * @brief Qt widget that hosts OpenGL-based trace visualizations.
 */
class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param parent Optional parent widget.
     */
    explicit OpenGLWidget(QWidget* parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~OpenGLWidget() override;

    /**
     * @brief Sets the active trace renderer.
     * @param renderer Shared pointer to a trace renderer.
     */
    void setRenderer(std::shared_ptr<ITraceRenderer> renderer);

protected:
    /**
     * @brief Initializes OpenGL state.
     */
    void initializeGL() override;

    /**
     * @brief Handles OpenGL viewport resize.
     * @param w Width.
     * @param h Height.
     */
    void resizeGL(int w, int h) override;

    /**
     * @brief Paints the widget using the current renderer.
     */
    void paintGL() override;

private:
    std::shared_ptr<ITraceRenderer> traceRenderer; ///< Current rendering strategy.
};