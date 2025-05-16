#include "Neuron.h"

Neuron::Neuron(double tau_, double threshold, double reset)
    : V(0.0), V_thresh(threshold), V_reset(reset), tau(tau_), spike(false) {}

void Neuron::update(double inputCurrent, double dt) {
    V += (dt / tau) * (-V + inputCurrent);
    if (V >= V_thresh) {
        V = V_reset;
        spike = true;
    } else {
        spike = false;
    }
}

bool Neuron::fired() const {
    return spike;
}

double Neuron::getVoltage() const {
    return V;
}
