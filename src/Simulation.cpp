#include "Simulation.h"

Simulation::Simulation(int neuronCount) {
    for (int i = 0; i < neuronCount; ++i) {
        m_neurons.emplace_back();
    }
}

void Simulation::step(double dt) {
    for (auto& neuron : m_neurons) {
        neuron.update(m_inputCurrent, dt);
    }
}

void Simulation::setInputCurrent(double current) {
    m_inputCurrent = current;
}

double Simulation::getInputCurrent() const {
    return m_inputCurrent;
}

const std::vector<Neuron>& Simulation::neurons() const {
    return m_neurons;
}
