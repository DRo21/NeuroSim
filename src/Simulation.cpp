#include <algorithm>
#include <random>
#include "Simulation.h"

/**
 * @brief Initializes the simulation with a given number of diverse neurons.
 */
Simulation::Simulation(int neuronCount) {
    m_neurons.reserve(neuronCount);

    std::default_random_engine rng(std::random_device{}());
    std::uniform_real_distribution<double> noiseA(-0.005, 0.005);
    std::uniform_real_distribution<double> noiseB(-0.01, 0.01);
    std::uniform_real_distribution<double> noiseC(-5.0, 5.0);
    std::uniform_real_distribution<double> noiseD(-2.0, 2.0);

    for (int i = 0; i < neuronCount; ++i) {
        double a = 0.02 + noiseA(rng);   // typical a: 0.02
        double b = 0.2 + noiseB(rng);    // typical b: 0.2
        double c = -65.0 + noiseC(rng);  // typical c: -65
        double d = 8.0 + noiseD(rng);    // typical d: 8

        m_neurons.emplace_back(a, b, c, d);
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

/**
 * @brief Converts the current neuron voltages into a 2D normalized heatmap grid.
 * 
 * This version tiles neuron voltages across the entire grid.
 *
 * @param width Number of columns in the output grid.
 * @param height Number of rows in the output grid.
 * @return std::vector<float> Flattened grid of voltage values mapped from [-80, 30] to [0, 1].
 */
std::vector<float> Simulation::getVoltageGrid(int width, int height) const {
    std::vector<float> grid(width * height, 0.0f);
    int neuronCount = static_cast<int>(m_neurons.size());

    if (neuronCount == 0) {
        return grid; // No neurons: return empty grid
    }

    for (int i = 0; i < width * height; ++i) {
        int neuronIndex = i % neuronCount;  // Wrap around neurons
        float v = m_neurons[neuronIndex].getVoltage();
        float normalized = (v + 80.0f) / 110.0f;
        normalized = std::clamp(normalized, 0.0f, 1.0f);
        grid[i] = normalized;
    }

    return grid;
}
