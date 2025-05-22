/**
 * @file IntegrateAndFireNeuron.h
 * @brief Defines the leaky integrate-and-fire neuron model used in the simulation.
 * @author Dario Romandini
 */

#ifndef INTEGRATE_AND_FIRE_NEURON_H
#define INTEGRATE_AND_FIRE_NEURON_H

#include "Neuron.h"

/**
 * @class IntegrateAndFireNeuron
 * @brief A simple leaky integrate-and-fire neuron model.
 *
 * Models membrane voltage dynamics with an exponential decay toward resting potential,
 * a threshold-based spiking mechanism, and instantaneous voltage reset after a spike.
 */
class IntegrateAndFireNeuron : public Neuron
{
public:
    /**
     * @brief Construct a neuron with configurable parameters.
     * @param v_rest Resting potential (mV).
     * @param v_thresh Spiking threshold (mV).
     * @param tau Membrane time constant (ms).
     * @param reset_v Voltage to reset to after a spike (mV).
     */
    IntegrateAndFireNeuron(double v_rest = -65.0,
                           double v_thresh = -50.0,
                           double tau = 20.0,
                           double reset_v = -65.0);

    /**
     * @brief Update the neuron's state by one time step.
     * @param dt Time step in milliseconds.
     */
    void update(double dt) override;

    /**
     * @brief Receive synaptic current from connected neurons.
     * @param i_syn Synaptic current (nA).
     */
    void receiveSynapticCurrent(double i_syn) override;

    /**
     * @brief Whether the neuron spiked during the last update.
     * @return True if spiked, false otherwise.
     */
    bool hasSpiked() const override;

    /**
     * @brief Time of the last spike relative to current step.
     * @return Time since last spike (ms).
     */
    double lastSpikeTime() const override;

    /**
     * @brief Get the current membrane potential.
     * @return Membrane voltage (mV).
     */
    double getVoltage() const override;

    /**
     * @brief Set external input current to be applied this time step.
     * @param input External current (nA).
     */
    void setInputCurrent(double input) override;

private:
    double v_;             ///< Current membrane voltage
    double v_rest_;        ///< Resting potential
    double v_thresh_;      ///< Spiking threshold
    double reset_v_;       ///< Reset potential after spike
    double tau_;           ///< Membrane time constant
    double i_syn_;         ///< Incoming synaptic current
    double i_ext_;         ///< External input current
    bool spiked_;          ///< Whether neuron spiked on last step
    double last_spike_t_;  ///< Time since last spike (not used in time tracking)
};

#endif // INTEGRATE_AND_FIRE_NEURON_H
