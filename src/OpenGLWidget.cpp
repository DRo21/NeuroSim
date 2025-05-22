/**
 * @file OpenGLWidget.cpp
 * @brief Implements OpenGLWidget for rendering trace visualizations via QPainter and OpenGL context. 
 * @author Dario Romandini
 */

#include "OpenGLWidget.h"
#include <QPainter>

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{}

OpenGLWidget::~OpenGLWidget() = default;

void OpenGLWidget::setRenderer(std::shared_ptr<ITraceRenderer> renderer)
{
    traceRenderer = std::move(renderer);
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (traceRenderer) {
        QPainter painter(this);
        traceRenderer->render(painter, rect());
    }
}
