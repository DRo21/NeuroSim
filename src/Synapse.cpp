/**
 * @file Synapse.cpp
 * @brief Implementation of Synapse, which delivers current on presynaptic spike activity.
 * @author Dario Romandini
 */

#include "Synapse.h"

Synapse::Synapse(int srcIndex, int dstIndex, double weight)
    : src_(srcIndex), dst_(dstIndex), weight_(weight)
{}

void Synapse::propagate(const std::vector<std::unique_ptr<Neuron>>& neurons) const
{
    if (neurons[src_]->hasSpiked()) {
        neurons[dst_]->receiveSynapticCurrent(weight_);
    }
}

int Synapse::src() const { return src_; }
int Synapse::dst() const { return dst_; }
double Synapse::weight() const { return weight_; }

void Synapse::setWeight(double w) { weight_ = w; }
