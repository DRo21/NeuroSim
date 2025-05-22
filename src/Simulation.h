/**
 * @file Simulation.h
 * @brief Manages a spiking neural network grid and synaptic connections.
 * @author Dario Romandini
 */

#ifndef SIMULATION_H
#define SIMULATION_H

#include "Neuron.h"
#include "Synapse.h"
#include <vector>
#include <memory>
#include <utility>

/**
 * @class Simulation
 * @brief Manages a network of spiking neurons and synaptic interactions.
 *
 * Encapsulates a 2D grid of neurons, a list of synaptic connections,
 * and spike-event recording. Provides the main step-based update loop and
 * access to voltages and spike data for visualization.
 */
class Simulation
{
public:
    /**
     * @brief Constructs a Simulation.
     * @param nx Grid width (columns).
     * @param ny Grid height (rows).
     * @param dt Integration time step in milliseconds.
     */
    Simulation(int nx, int ny, double dt = 0.1);

    /** @brief Initialize or reset all neurons. */
    void initializeNeurons();

    /**
     * @brief Create random connections between neurons.
     * @param p Probability of a connection between two neurons.
     * @param weight Synaptic weight in nanoamperes (nA).
     */
    void connectRandom(double p, double weight);

    /**
     * @brief Create local connections within a radius.
     * @param radius Maximum distance (in grid units).
     * @param weight Synaptic weight (nA).
     */
    void connectByProximity(double radius, double weight);

    /** @brief Advance the network by one simulation step (dt). */
    void step();

    /** @return Total number of neurons (nx × ny). */
    int neuronCount() const;

    /** @return Number of columns in the neuron grid. */
    int nx() const;

    /** @return Number of rows in the neuron grid. */
    int ny() const;

    /**
     * @brief Get a pointer to a neuron by index.
     * @param idx Linear index of the neuron.
     * @return Pointer to Neuron.
     */
    Neuron* getNeuron(int idx) const;

    /** @return Current simulation time in milliseconds. */
    double currentTime() const;

    /**
     * @brief Get spike history.
     * @return Vector of (time, neuron index) pairs.
     */
    const std::vector<std::pair<double, int>>& spikeEvents() const;

    /**
     * @brief Calculate spike rate for a neuron over a time window.
     * @param idx Neuron index.
     * @param window_ms Time window in milliseconds.
     * @return Spike rate in Hz.
     */
    double getSpikeRate(int idx, double window_ms) const;

    /**
     * @brief Estimate spike amplitude (proxy).
     * @param idx Neuron index.
     * @param window_ms Not currently used.
     * @return Current membrane voltage (as proxy for amplitude).
     */
    double getSpikeAmplitude(int idx, double window_ms) const;

    /**
     * @brief Set uniform external input current to all neurons.
     * @param current Input current in nA.
     */
    void setInputCurrent(double current);

    /**
     * @brief Select a neuron for external tracking (e.g., in trace views).
     * @param index Neuron index.
     */
    void setSelectedNeuron(int index);

private:
    int nx_, ny_;
    double dt_;
    double currentTime_;

    std::vector<std::unique_ptr<Neuron>> neurons_;
    std::vector<Synapse> synapses_;
    std::vector<std::pair<double, int>> events_;

    double globalInputCurrent_ = 0.0;
    int selectedNeuronIndex_ = -1;

    /** @brief Convert 2D grid coordinates to a flat array index. */
    int index(int x, int y) const { return y * nx_ + x; }
};

#endif // SIMULATION_H
