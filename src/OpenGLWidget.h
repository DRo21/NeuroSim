#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector>
#include <QTimer>

/**
 * @class OpenGLWidget
 * @brief Displays a real-time voltage trace plot using OpenGL.
 *
 * This widget renders the voltage of a selected neuron over time.
 */
class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    /**
     * @brief Constructs the OpenGLWidget.
     * @param parent Optional parent widget.
     */
    explicit OpenGLWidget(QWidget* parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~OpenGLWidget() override;

    /**
     * @brief Adds a new voltage sample to the plot.
     * @param voltage The voltage value to add.
     */
    void addVoltageSample(float voltage);

protected:
    /**
     * @brief Initializes OpenGL state and resources.
     */
    void initializeGL() override;

    /**
     * @brief Handles widget resizing events.
     * @param w New width.
     * @param h New height.
     */
    void resizeGL(int w, int h) override;

    /**
     * @brief Renders the voltage trace plot.
     */
    void paintGL() override;

private:
    QVector<float> voltageSamples; ///< Buffer storing recent voltage samples.
    int maxSamples = 1000;         ///< Maximum number of samples to display.

    float minVoltage = -80.0f;     ///< Minimum voltage expected (for scaling).
    float maxVoltage = 50.0f;      ///< Maximum voltage expected (for scaling).
};
