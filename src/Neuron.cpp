#include "Neuron.h"

/**
 * @brief Constructs a Neuron with specified Izhikevich model parameters.
 *
 * Initializes the membrane potential to -65 mV and recovery variable accordingly.
 */
Neuron::Neuron(double a_, double b_, double c_, double d_)
    : v(-65.0), u(b_ * -65.0), a(a_), b(b_), c(c_), d(d_), spike(false), synapticInput(0.0) {}

/**
 * @brief Updates the neuron state using the Izhikevich model.
 *
 * Performs numerical integration using Euler's method for 1 ms duration
 * with `1/dt` substeps. Adds accumulated synaptic input to external current.
 *
 * @param inputCurrent External input current applied this timestep.
 * @param dt Time step for integration (e.g., 0.1 ms).
 */
void Neuron::update(double inputCurrent, double dt) {
    spike = false;

    double totalInput = inputCurrent + synapticInput;
    synapticInput = 0.0; // reset buffer after applying

    for (int i = 0; i < static_cast<int>(1.0 / dt); ++i) {
        double dv = 0.04 * v * v + 5 * v + 140 - u + totalInput;
        double du = a * (b * v - u);
        v += dt * dv;
        u += dt * du;

        if (v >= 30.0) {
            v = c;
            u += d;
            spike = true;
        }
    }
}

/**
 * @brief Buffers synaptic input to be applied on next update.
 *
 * This allows external sources (e.g., synapses) to inject current
 * without immediately changing the neuron’s state until `update()` is called.
 *
 * @param current Synaptic input current (excitatory or inhibitory).
 */
void Neuron::receiveSynapticInput(double current) {
    synapticInput += current;
}

/**
 * @brief Returns whether the neuron fired during the last update.
 *
 * @return true if the neuron’s voltage exceeded threshold and spiked.
 */
bool Neuron::fired() const {
    return spike;
}

/**
 * @brief Returns the current membrane voltage.
 *
 * @return double The neuron’s membrane potential (in millivolts).
 */
double Neuron::getVoltage() const {
    return v;
}
