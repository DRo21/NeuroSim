/**
 * @file ControlPanelWidget.h
 * @brief GUI widget for controlling simulation parameters in NeuroSim.
 * @author Dario Romandini
 */

#ifndef CONTROLPANELWIDGET_H
#define CONTROLPANELWIDGET_H

#include <QWidget>

class QPushButton;
class QSpinBox;
class QSlider;
class QComboBox;

/**
 * @class ControlPanelWidget
 * @brief A widget providing controls for starting/stopping the simulation,
 * adjusting grid size, input current, display mode, and selecting neurons.
 */
class ControlPanelWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param parent Parent widget.
     */
    explicit ControlPanelWidget(QWidget* parent = nullptr);

signals:
    void startSimulation();
    void stopSimulation();
    void gridSizeChanged(int nx, int ny);
    void inputCurrentChanged(double current);
    void displayModeChanged(int modeIndex);
    void neuronSelected(int neuronIndex);

private slots:
    void handleStartStop();
    void handleGridXChanged(int value);
    void handleGridYChanged(int value);
    void handleCurrentChanged(int value);
    void handleModeChanged(int index);
    void handleNeuronSelection(int index);

private:
    QPushButton*   startStopButton_;
    QSpinBox*      gridXSpin_;
    QSpinBox*      gridYSpin_;
    QSlider*       currentSlider_;
    QComboBox*     displayModeCombo_;
    QComboBox*     neuronSelectCombo_;
    bool           running_;
};

#endif // CONTROLPANELWIDGET_H
