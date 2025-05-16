#include "Simulation.h"

/**
 * @brief Initializes the simulation with a given number of default neurons.
 */
Simulation::Simulation(int neuronCount) {
    for (int i = 0; i < neuronCount; ++i) {
        m_neurons.emplace_back();
    }
}

/**
 * @brief Updates all neurons in the simulation by one time step.
 */
void Simulation::step(double dt) {
    for (auto& neuron : m_neurons) {
        neuron.update(m_inputCurrent, dt);
    }
}

/**
 * @brief Sets the input current applied to all neurons.
 */
void Simulation::setInputCurrent(double current) {
    m_inputCurrent = current;
}

/**
 * @brief Gets the current input current.
 */
double Simulation::getInputCurrent() const {
    return m_inputCurrent;
}

/**
 * @brief Returns the list of neurons in the simulation.
 */
const std::vector<Neuron>& Simulation::neurons() const {
    return m_neurons;
}
