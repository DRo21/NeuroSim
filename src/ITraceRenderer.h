/**
 * @file ITraceRenderer.h
 * @brief Interface for trace rendering strategies in OpenGLWidget.
 * @author Dario Romandini
 */

#pragma once
#include <QPainter>
#include <QRect>

/**
 * @interface ITraceRenderer
 * @brief Abstract base class for rendering trace visualizations.
 *
 * Implementations define how to render activity traces such as voltage over time.
 * Decouples UI components from the specific rendering logic.
 */
class ITraceRenderer {
public:
    virtual ~ITraceRenderer() = default;

    /**
     * @brief Render the trace using the given QPainter.
     * @param painter Painter to draw onto.
     * @param bounds Rectangle defining the drawing area.
     */
    virtual void render(QPainter& painter, const QRect& bounds) = 0;
};
