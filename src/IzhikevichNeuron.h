/**
 * @file IzhikevichNeuron.h
 * @brief Declaration of the IzhikevichNeuron class for NeuroSim.
 * @author Dario Romandini
 */

#ifndef IZHIKEVICH_NEURON_H
#define IZHIKEVICH_NEURON_H

#include "Neuron.h"

/**
 * @class IzhikevichNeuron
 * @brief Implements a biologically plausible spiking neuron using the Izhikevich model.
 *
 * This neuron simulates spiking behavior using a 2-variable system:
 * membrane potential (v) and a recovery variable (u). The model supports
 * various firing patterns by adjusting four parameters: a, b, c, and d.
 *
 * This class conforms to the Neuron interface and can be used
 * interchangeably in simulation components.
 */
class IzhikevichNeuron : public Neuron
{
public:
    /**
     * @brief Constructs an Izhikevich neuron with custom or default parameters.
     *
     * @param a Recovery time constant (default 0.02).
     * @param b Sensitivity of recovery variable u to membrane voltage (default 0.2).
     * @param c Reset voltage after a spike (mV, default -65.0).
     * @param d Reset increment of u after a spike (default 8.0).
     */
    IzhikevichNeuron(double a = 0.02, double b = 0.2, double c = -65.0, double d = 8.0);

    /// @copydoc Neuron::update()
    void update(double dt) override;

    /// @copydoc Neuron::receiveSynapticCurrent()
    void receiveSynapticCurrent(double i_syn) override;

    /// @copydoc Neuron::hasSpiked()
    bool hasSpiked() const override;

    /// @copydoc Neuron::lastSpikeTime()
    double lastSpikeTime() const override;

    /// @copydoc Neuron::getVoltage()
    double getVoltage() const override;

    /// @copydoc Neuron::setInputCurrent()
    void setInputCurrent(double input) override;

private:
    double v_;             ///< Membrane potential (mV)
    double u_;             ///< Recovery variable
    double a_, b_, c_, d_; ///< Izhikevich model parameters
    double i_syn_;         ///< Accumulated synaptic input (nA)
    double i_ext_;         ///< External injected current (nA)
    bool   spiked_;        ///< Spike flag (true if neuron fired on last update)
    double last_spike_t_;  ///< Timestamp of last spike (ms)
};

#endif // IZHIKEVICH_NEURON_H
