#include "IntegrateAndFireNeuron.h"

IntegrateAndFireNeuron::IntegrateAndFireNeuron(double v_rest, double v_thresh,
                                               double tau, double reset_v)
    : v_(v_rest), v_rest_(v_rest), v_thresh_(v_thresh),
      reset_v_(reset_v), tau_(tau),
      i_syn_(0.0), i_ext_(0.0),
      spiked_(false), last_spike_t_(-1e9)
{}

void IntegrateAndFireNeuron::update(double dt)
{
    spiked_ = false;

    double input = i_ext_ + i_syn_;
    v_ += dt * (-(v_ - v_rest_) + input) / tau_;

    if (v_ >= v_thresh_) {
        spiked_ = true;
        v_ = reset_v_;
        last_spike_t_ = 0.0;
    }

    i_syn_ = 0.0;
    i_ext_ = 0.0;
}

void IntegrateAndFireNeuron::receiveSynapticCurrent(double i_syn)
{
    i_syn_ += i_syn;
}

void IntegrateAndFireNeuron::setInputCurrent(double input)
{
    i_ext_ = input;
}

bool IntegrateAndFireNeuron::hasSpiked() const
{
    return spiked_;
}

double IntegrateAndFireNeuron::lastSpikeTime() const
{
    return last_spike_t_;
}

double IntegrateAndFireNeuron::getVoltage() const
{
    return v_;
}
