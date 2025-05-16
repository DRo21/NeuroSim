#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <deque>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    OpenGLWidget(QWidget *parent = nullptr);

public slots:
    void addVoltageSample(float voltage);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    std::deque<float> voltageHistory;
    const size_t maxSamples = 200;
};
