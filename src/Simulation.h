#pragma once

#include <vector>
#include "Neuron.h"

/**
 * @class Simulation
 * @brief Manages a population of Izhikevich neurons and their state.
 *
 * - Holds a vector of `Neuron` objects.
 * - Applies an external input current to each neuron on each time step.
 * - Provides methods to advance (step) the simulation and to retrieve a 2D
 *   grid of normalized voltages for heatmap rendering.
 * - Tracks a “selected neuron” index (for potential future trace overlay).
 */
class Simulation {
public:
    /**
     * @brief Constructs a Simulation with a specified number of neurons.
     * @param neuronCount Number of neurons to create; each is initialized with
     *                    random variation in Izhikevich parameters.
     */
    Simulation(int neuronCount);

    /**
     * @brief Advances all neurons in the simulation by one time step.
     * @param dt Time step (in the same units that `Neuron::update` expects).
     */
    void step(double dt);

    /**
     * @brief Returns a constant reference to the internal vector of neurons.
     * @return const std::vector<Neuron>& Full neuron list.
     */
    const std::vector<Neuron>& neurons() const;

    /**
     * @brief Sets the uniform external input current for all neurons.
     * @param current The input current (arbitrary units).
     */
    void setInputCurrent(double current);

    /**
     * @brief Retrieves the current external input current.
     * @return double The input current value in use.
     */
    double getInputCurrent() const;

    /**
     * @brief Generates a flattened grid of normalized voltages for heatmap.
     *
     * For each cell in a `width × height` grid, picks a neuron index by wrapping
     * around `m_neurons.size()`. Takes that neuron’s voltage `v` in [-80, 30],
     * normalizes into [0,1] via `(v + 80) / 110`, clamps to [0,1], and stores it.
     *
     * @param width  Number of columns in output grid.
     * @param height Number of rows in output grid.
     * @return std::vector<float> Flattened `width * height` vector of normalized voltages.
     */
    std::vector<float> getVoltageGrid(int width, int height) const;

    /**
     * @brief Sets which neuron is “selected” for detailed plotting (index).
     * @param index Index of the neuron to select. Clamped to valid range if out‐of‐bounds.
     */
    void setSelectedNeuron(int index);

    /**
     * @brief Retrieves the currently selected neuron index.
     * @return int Index of the selected neuron.
     */
    int getSelectedNeuron() const;

private:
    std::vector<Neuron> m_neurons;   ///< Underlying vector of all neuron instances.
    double m_inputCurrent = 0.0;     ///< Input current applied to every neuron each step.
    int m_selectedNeuron = 0;        ///< Index of neuron selected for detailed trace.
};
