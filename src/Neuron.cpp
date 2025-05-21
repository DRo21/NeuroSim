// Neuron.cpp

#include "Neuron.h"

constexpr double SPIKE_THRESHOLD = 30.0;    ///< Membrane potential threshold for spike (mV)
constexpr double RESET_POTENTIAL = -65.0;   ///< Default reset potential (mV)
constexpr double DEFAULT_V = -65.0;         ///< Default initial membrane potential (mV)
constexpr double DEFAULT_U_SCALE = -65.0;   ///< Scale for u initial value

/**
 * @brief Constructs a Neuron with specified Izhikevich model parameters.
 * @param a Parameter a of the Izhikevich model.
 * @param b Parameter b of the Izhikevich model.
 * @param c Parameter c of the Izhikevich model (reset potential).
 * @param d Parameter d of the Izhikevich model.
 */
Neuron::Neuron(double a, double b, double c, double d)
    : v_(DEFAULT_V),
      u_(b * DEFAULT_U_SCALE),
      a_(a),
      b_(b),
      c_(c),
      d_(d),
      spike_(false),
      synapticInput_(0.0)
{}

/**
 * @brief Updates the neuron state using the Izhikevich model.
 *
 * Performs Euler integration over 1.0 ms of simulated time,
 * subdivided into dt‐sized substeps, with both external and
 * buffered synaptic input.
 *
 * @param inputCurrent External input current to apply this step.
 * @param dt Time step for integration (ms).
 */
void Neuron::update(double inputCurrent, double dt)
{
    spike_ = false;

    // Combine external input with any buffered synaptic input
    double totalInput = inputCurrent + synapticInput_;
    synapticInput_ = 0.0;

    // Number of micro‐steps to cover 1 ms
    int substeps = static_cast<int>(1.0 / dt);
    for (int i = 0; i < substeps; ++i) {
        double dv = 0.04 * v_ * v_ + 5.0 * v_ + 140.0 - u_ + totalInput;
        double du = a_ * (b_ * v_ - u_);

        v_ += dt * dv;
        u_ += dt * du;

        if (v_ >= SPIKE_THRESHOLD) {
            v_ = c_;           // reset membrane potential
            u_ += d_;          // apply after‐spike recovery
            spike_ = true;
        }
    }
}

/**
 * @brief Buffers synaptic input to be applied during the next update().
 * @param current Synaptic current (nA) to add.
 */
void Neuron::receiveSynapticInput(double current)
{
    synapticInput_ += current;
}

/**
 * @brief Query whether the neuron fired (spiked) in the last update().
 * @return True if a spike occurred, false otherwise.
 */
bool Neuron::fired() const
{
    return spike_;
}

/**
 * @brief Get the current membrane potential.
 * @return Membrane potential (mV).
 */
double Neuron::getVoltage() const
{
    return v_;
}
