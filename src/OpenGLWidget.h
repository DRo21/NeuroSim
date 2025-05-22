/**
 * @file OpenGLWidget.h
 * @brief Qt widget for rendering traces using OpenGL and QPainter.
 * @author Dario Romandini
 */

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
    explicit OpenGLWidget(QWidget* parent = nullptr);
    ~OpenGLWidget() override;

    void setRenderer(std::shared_ptr<ITraceRenderer> renderer);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    std::shared_ptr<ITraceRenderer> traceRenderer;
};
