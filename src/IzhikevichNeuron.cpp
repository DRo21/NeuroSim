/**
 * @file IzhikevichNeuron.cpp
 * @brief Implementation of the IzhikevichNeuron class for NeuroSim.
 * @author Dario Romandini
 */

#include "IzhikevichNeuron.h"

IzhikevichNeuron::IzhikevichNeuron(double a, double b, double c, double d)
    : v_(-65.0), u_(b * -65.0),
      a_(a), b_(b), c_(c), d_(d),
      i_syn_(0.0), i_ext_(0.0),
      spiked_(false), last_spike_t_(-1e9)
{}

void IzhikevichNeuron::update(double dt)
{
    spiked_ = false;
    double input = i_ext_ + i_syn_;
    i_syn_ = 0.0;
    i_ext_ = 0.0;

    int steps = static_cast<int>(1.0 / dt);
    for (int i = 0; i < steps; ++i) {
        double dv = 0.04 * v_ * v_ + 5.0 * v_ + 140.0 - u_ + input;
        double du = a_ * (b_ * v_ - u_);
        v_ += dt * dv;
        u_ += dt * du;

        if (v_ >= 30.0) {
            v_ = c_;
            u_ += d_;
            spiked_ = true;
            last_spike_t_ = 0.0;
        }
    }
}

void IzhikevichNeuron::receiveSynapticCurrent(double i_syn)
{
    i_syn_ += i_syn;
}

void IzhikevichNeuron::setInputCurrent(double input)
{
    i_ext_ = input;
}

bool IzhikevichNeuron::hasSpiked() const
{
    return spiked_;
}

double IzhikevichNeuron::lastSpikeTime() const
{
    return last_spike_t_;
}

double IzhikevichNeuron::getVoltage() const
{
    return v_;
}
