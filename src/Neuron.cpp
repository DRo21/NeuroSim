#include "Neuron.h"

Neuron::Neuron(double a_, double b_, double c_, double d_)
    : v(-65.0), u(b_ * -65.0), a(a_), b(b_), c(c_), d(d_), spike(false) {}

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

bool Neuron::fired() const {
    return spike;
}

double Neuron::getVoltage() const {
    return v;
}
