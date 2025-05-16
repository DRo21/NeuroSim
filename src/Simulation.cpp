#include "Simulation.h"
#include <cmath>

Simulation::Simulation(int neuronCount) {
    for (int i = 0; i < neuronCount; ++i) {
        m_neurons.emplace_back();
    }
}

void Simulation::step(double dt) {
    for (auto& neuron : m_neurons) {
        double input = 1.1 + 0.5 * sin(neuron.getVoltage());
        neuron.update(input, dt);
    }
}

const std::vector<Neuron>& Simulation::neurons() const {
    return m_neurons;
}
