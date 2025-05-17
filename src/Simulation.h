#pragma once

#include <vector>
#include "Neuron.h"

/**
 * @class Simulation
 * @brief Manages a population of neurons and their simulation state.
 *
 * Handles updating of all neurons, applying input current, and accessing voltage
 * data for visualization. Also tracks a selected neuron for focused analysis.
 */
class Simulation {
public:
    /**
     * @brief Constructs a simulation with a given number of neurons.
     * @param neuronCount Number of neurons in the simulation.
     */
    Simulation(int neuronCount);

    /**
     * @brief Advances the simulation by a time step.
     * @param dt Time step for simulation update.
     */
    void step(double dt);

    /**
     * @brief Returns a constant reference to the list of neurons.
     * @return const std::vector<Neuron>& Neuron list.
     */
    const std::vector<Neuron>& neurons() const;

    /**
     * @brief Sets the external input current for all neurons.
     * @param current The current value to apply.
     */
    void setInputCurrent(double current);

    /**
     * @brief Returns the current input current value.
     * @return double Input current.
     */
    double getInputCurrent() const;

    /**
     * @brief Converts neuron voltages into a normalized 2D heatmap grid.
     * @param width Desired width of the heatmap.
     * @param height Desired height of the heatmap.
     * @return std::vector<float> A flattened vector representing the heatmap.
     */
    std::vector<float> getVoltageGrid(int width, int height) const;

    /**
     * @brief Sets the index of the currently selected neuron.
     * 
     * This neuron is used for focused visualization (e.g. voltage plotting).
     * If the index is out of bounds, it is clamped to the nearest valid index.
     *
     * @param index Index of the neuron to select.
     */
    void setSelectedNeuron(int index);

    /**
     * @brief Returns the index of the currently selected neuron.
     * @return int Selected neuron index.
     */
    int getSelectedNeuron() const;

private:
    std::vector<Neuron> m_neurons;  ///< Vector of neurons in the simulation.
    double m_inputCurrent = 10.0;   ///< Input current applied to each neuron.
    int m_selectedNeuron = 0;       ///< Currently selected neuron for detailed plotting.
};
