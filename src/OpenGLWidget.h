#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <deque>
#include <QVector>

/**
 * @class OpenGLWidget
 * @brief Renders a real-time voltage trace (line plot) using OpenGL + QPainter.
 *
 * Maintains a circular buffer of the most recent voltage samples (up to maxSamples).
 * Each call to addVoltageSample() pushes a new value; paintGL() draws the line.
 */
class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    /**
     * @brief Constructs the OpenGLWidget and preallocates storage.
     * @param parent Optional parent widget.
     */
    explicit OpenGLWidget(QWidget* parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~OpenGLWidget() override;

    /**
     * @brief Adds a new voltage sample to the buffer and requests a repaint.
     * @param voltage Value (e.g., in mV) to append to the trace.
     */
    void addVoltageSample(float voltage);

    /**
     * @brief Clears all stored voltage samples, effectively resetting the trace.
     */
    void clearVoltageTrace();

protected:
    /**
     * @brief Initializes OpenGL functions and state (once).
     */
    void initializeGL() override;

    /**
     * @brief Updates OpenGL viewport on widget resize.
     * @param w New width (pixels).
     * @param h New height (pixels).
     */
    void resizeGL(int w, int h) override;

    /**
     * @brief Renders the voltage trace as a green polyline on a black background.
     *
     * Uses QPainter on top of the cleared OpenGL buffer for anti-aliased lines.
     */
    void paintGL() override;

private:
    std::deque<float> voltageSamples; ///< Circular buffer of recent samples.
    const int maxSamples = 500;       ///< Maximum number of samples to keep.

    // Voltage range for normalization (-80 mV to +50 mV)
    const float minVoltage = -80.0f;
    const float maxVoltage =  50.0f;
};
