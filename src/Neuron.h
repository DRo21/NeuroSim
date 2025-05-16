#pragma once

class Neuron {
public:
    Neuron(double a = 0.02, double b = 0.2, double c = -65.0, double d = 8.0);

    void update(double inputCurrent, double dt);
    bool fired() const;
    double getVoltage() const;

private:
    double v;
    double u;
    double a, b;
    double c, d;
    bool spike;
};
