#pragma once
#include <vector>
#include "Neuron.h"

class Simulation {
public:
    Simulation(int neuronCount);
    void step(double dt);
    const std::vector<Neuron>& neurons() const;

    void setInputCurrent(double current);
    double getInputCurrent() const;

private:
    std::vector<Neuron> m_neurons;
    double m_inputCurrent = 10.0;
};
