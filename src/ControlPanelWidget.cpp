/**
 * @file ControlPanelWidget.cpp
 * @brief Implementation of the ControlPanelWidget class for simulation control UI.
 * @author Dario Romandini
 */

#include "ControlPanelWidget.h"
#include <QPushButton>
#include <QSpinBox>
#include <QSlider>
#include <QComboBox>
#include <QHBoxLayout>
#include <QFormLayout>

ControlPanelWidget::ControlPanelWidget(QWidget* parent)
    : QWidget(parent), running_(false)
{
    startStopButton_    = new QPushButton(tr("Start"), this);
    gridXSpin_          = new QSpinBox(this);
    gridYSpin_          = new QSpinBox(this);
    currentSlider_      = new QSlider(Qt::Horizontal, this);
    displayModeCombo_   = new QComboBox(this);
    neuronSelectCombo_  = new QComboBox(this);

    gridXSpin_->setRange(1, 100);
    gridYSpin_->setRange(1, 100);
    gridXSpin_->setValue(10);
    gridYSpin_->setValue(10);
    currentSlider_->setRange(0, 100);
    displayModeCombo_->addItems({tr("Voltage"), tr("Spike Rate"), tr("Amplitude")});
    neuronSelectCombo_->addItem(tr("All"));

    auto form = new QFormLayout;
    form->addRow(tr("Grid X:"), gridXSpin_);
    form->addRow(tr("Grid Y:"), gridYSpin_);
    form->addRow(tr("Current (nA):"), currentSlider_);
    form->addRow(tr("Display Mode:"), displayModeCombo_);
    form->addRow(tr("Neuron:"), neuronSelectCombo_);

    auto mainLayout = new QHBoxLayout;
    mainLayout->addWidget(startStopButton_);
    mainLayout->addLayout(form);
    setLayout(mainLayout);

    connect(startStopButton_, &QPushButton::clicked, this, &ControlPanelWidget::handleStartStop);
    connect(gridXSpin_, qOverload<int>(&QSpinBox::valueChanged), this, &ControlPanelWidget::handleGridXChanged);
    connect(gridYSpin_, qOverload<int>(&QSpinBox::valueChanged), this, &ControlPanelWidget::handleGridYChanged);
    connect(currentSlider_, &QSlider::valueChanged, this, &ControlPanelWidget::handleCurrentChanged);
    connect(displayModeCombo_, qOverload<int>(&QComboBox::currentIndexChanged), this, &ControlPanelWidget::handleModeChanged);
    connect(neuronSelectCombo_, qOverload<int>(&QComboBox::currentIndexChanged), this, &ControlPanelWidget::handleNeuronSelection);
}

void ControlPanelWidget::handleStartStop()
{
    running_ = !running_;
    startStopButton_->setText(running_ ? tr("Stop") : tr("Start"));
    emit running_ ? startSimulation() : stopSimulation();
}

void ControlPanelWidget::handleGridXChanged(int x)
{
    emit gridSizeChanged(x, gridYSpin_->value());
}

void ControlPanelWidget::handleGridYChanged(int y)
{
    emit gridSizeChanged(gridXSpin_->value(), y);
}

void ControlPanelWidget::handleCurrentChanged(int val)
{
    emit inputCurrentChanged(static_cast<double>(val));
}

void ControlPanelWidget::handleModeChanged(int idx)
{
    emit displayModeChanged(idx);
}

void ControlPanelWidget::handleNeuronSelection(int idx)
{
    emit neuronSelected(idx);
}
