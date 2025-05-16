#include "Neuron.h"

/**
 * @brief Constructs a Neuron with specified Izhikevich model parameters.
 */
Neuron::Neuron(double a_, double b_, double c_, double d_)
    : v(-65.0), u(b_ * -65.0), a(a_), b(b_), c(c_), d(d_), spike(false) {}

/**
 * @brief Updates the neuron state using the Izhikevich model.
 * 
 * Integrates using Euler method over 1 ms with internal substeps.
 */
void Neuron::update(double inputCurrent, double dt) {
    spike = false;
    for (int i = 0; i < static_cast<int>(1.0 / dt); ++i) {
        double dv = 0.04 * v * v + 5 * v + 140 - u + inputCurrent;
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
 * @brief Returns whether the neuron fired during the last update.
 */
bool Neuron::fired() const {
    return spike;
}

/**
 * @brief Returns the current membrane voltage.
 */
double Neuron::getVoltage() const {
    return v;
}
