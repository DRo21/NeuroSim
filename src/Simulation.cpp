#include "Simulation.h"
#include <algorithm>
#include <random>

/**
 * @brief Constructs the Simulation and initializes each neuron.
 *
 * Each neuron is created using Izhikevich parameters (a, b, c, d) with slight random
 * variation to simulate biological diversity. The input current starts at 0.0.
 *
 * @param neuronCount Number of neurons to instantiate.
 */
Simulation::Simulation(int neuronCount) {
    m_neurons.reserve(neuronCount);

    // Random noise distributions for Izhikevich parameters
    std::default_random_engine rng(std::random_device{}());
    std::uniform_real_distribution<double> noiseA(-0.005, 0.005);
    std::uniform_real_distribution<double> noiseB(-0.01, 0.01);
    std::uniform_real_distribution<double> noiseC(-5.0, 5.0);
    std::uniform_real_distribution<double> noiseD(-2.0, 2.0);

    for (int i = 0; i < neuronCount; ++i) {
        double a = 0.02 + noiseA(rng);    // Typical a ≈ 0.02
        double b = 0.2  + noiseB(rng);    // Typical b ≈ 0.2
        double c = -65.0 + noiseC(rng);   // Typical c ≈ -65
        double d = 8.0   + noiseD(rng);   // Typical d ≈ 8

        m_neurons.emplace_back(a, b, c, d);
    }
}

/**
 * @brief Advances the simulation by one time step for all neurons.
 *
 * Calls `Neuron::update(inputCurrent, dt)` on each neuron, where `inputCurrent`
 * is the same for every neuron in this implementation.
 *
 * @param dt Time step to advance (e.g., 0.1).
 */
void Simulation::step(double dt) {
    for (auto& neuron : m_neurons) {
        neuron.update(m_inputCurrent, dt);
    }
}

/**
 * @brief Sets the uniform input current applied to every neuron.
 * @param current The new input current value.
 */
void Simulation::setInputCurrent(double current) {
    m_inputCurrent = current;
}

/**
 * @brief Returns the current external input current value.
 * @return double The input current.
 */
double Simulation::getInputCurrent() const {
    return m_inputCurrent;
}

/**
 * @brief Accessor for the internal neuron vector.
 * @return const std::vector<Neuron>& Reference to all neurons.
 */
const std::vector<Neuron>& Simulation::neurons() const {
    return m_neurons;
}

/**
 * @brief Builds a 2D grid of normalized voltages for heatmap display.
 *
 * - Each grid cell (at index i) wraps around to a neuron index (i % neuronCount).
 * - Retrieves that neuron’s voltage `v` in [-80, 30].
 * - Normalizes with `(v + 80) / 110`, clamps to [0,1], storing the result.
 *
 * @param width  Number of columns in output.
 * @param height Number of rows in output.
 * @return std::vector<float> Flattened vector length `width*height`.
 */
std::vector<float> Simulation::getVoltageGrid(int width, int height) const {
    std::vector<float> grid(width * height, 0.0f);
    int neuronCount = static_cast<int>(m_neurons.size());
    if (neuronCount == 0) {
        return grid;  // no neurons → empty (all zeros)
    }

    for (int i = 0; i < width * height; ++i) {
        int idx = i % neuronCount;
        float v = static_cast<float>(m_neurons[idx].getVoltage());
        float normalized = (v + 80.0f) / 110.0f;
        normalized = std::clamp(normalized, 0.0f, 1.0f);
        grid[i] = normalized;
    }
    return grid;
}

/**
 * @brief Selects a neuron index for detailed plotting (clamped to valid range).
 * @param index Desired neuron index. If out-of-range, it is clamped between [0, size−1].
 */
void Simulation::setSelectedNeuron(int index) {
    if (m_neurons.empty()) {
        m_selectedNeuron = 0;
    } else {
        m_selectedNeuron = std::clamp(index, 0, static_cast<int>(m_neurons.size() - 1));
    }
}

/**
 * @brief Returns the index of the currently selected neuron.
 * @return int Index in [0, size−1].
 */
int Simulation::getSelectedNeuron() const {
    return m_selectedNeuron;
}
