/**
 * @file Neuron.h
 * @brief Abstract base class representing a neuron model interface.
 * @author Dario Romandini
 */

#ifndef NEURON_H
#define NEURON_H

/**
 * @class Neuron
 * @brief Interface for neuron models (e.g., Izhikevich, LIF).
 *
 * Provides a standard API for updating state, handling synaptic input,
 * checking for spikes, accessing voltage, and setting input current.
 */
class Neuron
{
public:
    virtual ~Neuron() = default;

    /**
     * @brief Advance the neuron's state by a time step.
     * @param dt Time step in milliseconds.
     */
    virtual void update(double dt) = 0;

    /**
     * @brief Inject synaptic input current into the neuron.
     * @param i_syn Input current in nanoamperes (nA).
     */
    virtual void receiveSynapticCurrent(double i_syn) = 0;

    /**
     * @brief Determine if the neuron has spiked in the most recent step.
     * @return True if a spike occurred, false otherwise.
     */
    virtual bool hasSpiked() const = 0;

    /**
     * @brief Return the time of the last spike (if applicable).
     * @return Time in milliseconds.
     */
    virtual double lastSpikeTime() const = 0;

    /**
     * @brief Get the current membrane potential of the neuron.
     * @return Voltage in millivolts (mV).
     */
    virtual double getVoltage() const = 0;

    /**
     * @brief Set external input current to be used on the next update.
     * @param input External input current in nanoamperes (nA).
     */
    virtual void setInputCurrent(double input) = 0;
};

#endif // NEURON_H
