#pragma once

class Neuron {
public:
    Neuron(double tau = 10.0, double threshold = 1.0, double reset = 0.0);

    void update(double inputCurrent, double dt);
    bool fired() const;
    double getVoltage() const;

private:
    double V;
    double V_thresh;
    double V_reset;
    double tau;
    bool spike;
};
