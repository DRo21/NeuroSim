#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <deque>

/**
 * @brief A custom OpenGL widget for visualizing neuron membrane voltage over time.
 * 
 * This widget plots the voltage values on a real-time line graph.
 */
class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    /**
     * @brief Constructs the OpenGLWidget.
     * 
     * @param parent Optional parent widget.
     */
    explicit OpenGLWidget(QWidget *parent = nullptr);

    /**
     * @brief Adds a new voltage sample to the history buffer.
     * 
     * Triggers a repaint to display the updated graph.
     * 
     * @param voltage Membrane voltage value.
     */
    void addVoltageSample(float voltage);

protected:
    /**
     * @brief Initializes OpenGL context and settings.
     */
    void initializeGL() override;

    /**
     * @brief Handles OpenGL viewport resizing.
     * 
     * @param w New width.
     * @param h New height.
     */
    void resizeGL(int w, int h) override;

    /**
     * @brief Renders the voltage line graph.
     */
    void paintGL() override;

private:
    std::deque<float> voltageHistory; ///< Circular buffer of voltage samples.
    const size_t maxSamples;          ///< Maximum number of samples to keep.
};
