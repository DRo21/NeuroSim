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
 * This class encapsulates a 2D grid of neurons, a list of synaptic connections,
 * and spike-event recording. It provides the main step-based update loop and
 * access to statistics and voltages for visualization.
 */
class Simulation
{
public:
    /**
     * @brief Constructor for Simulation.
     * @param nx Number of columns in the neuron grid.
     * @param ny Number of rows in the neuron grid.
     * @param dt Time step size in milliseconds.
     */
    Simulation(int nx, int ny, double dt = 0.1);

    /** @brief Initialize and reset all neurons in the grid. */
    void initializeNeurons();

    /**
     * @brief Randomly connect neurons.
     * @param p Probability of connection per pair.
     * @param weight Synaptic weight (nA).
     */
    void connectRandom(double p, double weight);

    /**
     * @brief Connect neurons by proximity (within radius).
     * @param radius Euclidean radius (grid units).
     * @param weight Synaptic weight (nA).
     */
    void connectByProximity(double radius, double weight);

    /** @brief Advance simulation state by one time step (dt). */
    void step();

    /** @return Total number of neurons (nx * ny). */
    int neuronCount() const;

    /** @return Grid width (columns). */
    int nx() const;

    /** @return Grid height (rows). */
    int ny() const;

    /**
     * @brief Get pointer to a neuron by index.
     * @param idx Index in range [0, neuronCount()).
     * @return Neuron pointer.
     */
    Neuron* getNeuron(int idx) const;

    /** @return Current simulation time in milliseconds. */
    double currentTime() const;

    /**
     * @brief Get spike events from the start.
     * @return Vector of (time, neuron index) pairs.
     */
    const std::vector<std::pair<double, int>>& spikeEvents() const;

    /**
     * @brief Compute spike rate over a time window.
     * @param idx Neuron index.
     * @param window_ms Time window (ms).
     * @return Spike rate in Hz.
     */
    double getSpikeRate(int idx, double window_ms) const;

    /**
     * @brief Estimate spike amplitude for a neuron.
     * @param idx Neuron index.
     * @param window_ms Time window (currently unused).
     * @return Estimated amplitude (mV).
     */
    double getSpikeAmplitude(int idx, double window_ms) const;

    /**
     * @brief Set external input current for all neurons.
     * @param current Input current (nA).
     */
    void setInputCurrent(double current);

    /**
     * @brief Set a neuron to track (for visualization).
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

    /** @brief Convert grid coordinates to flat index. */
    int index(int x, int y) const { return y * nx_ + x; }
};

#endif // SIMULATION_H
