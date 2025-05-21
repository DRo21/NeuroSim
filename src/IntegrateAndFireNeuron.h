#ifndef INTEGRATE_AND_FIRE_NEURON_H
#define INTEGRATE_AND_FIRE_NEURON_H

#include "Neuron.h"

/**
 * @brief A simple leaky integrate-and-fire neuron model.
 */
class IntegrateAndFireNeuron : public Neuron
{
public:
    IntegrateAndFireNeuron(double v_rest = -65.0,
                           double v_thresh = -50.0,
                           double tau = 20.0,
                           double reset_v = -65.0);

    void update(double dt) override;
    void receiveSynapticCurrent(double i_syn) override;
    bool hasSpiked() const override;
    double lastSpikeTime() const override;
    double getVoltage() const override;
    void setInputCurrent(double input) override;

private:
    double v_, v_rest_, v_thresh_, reset_v_, tau_;
    double i_syn_, i_ext_;
    bool spiked_;
    double last_spike_t_;
};

#endif // INTEGRATE_AND_FIRE_NEURON_H
