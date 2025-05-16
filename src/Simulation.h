#pragma once
#include <vector>
#include "Neuron.h"

class Simulation {
public:
    Simulation(int neuronCount);
    void step(double dt);
    const std::vector<Neuron>& neurons() const;

private:
    std::vector<Neuron> m_neurons;
};
