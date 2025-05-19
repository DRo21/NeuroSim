#include "Synapse.h"

Synapse::Synapse(int sourceIndex, int targetIndex, double synapticWeight)
    : source(sourceIndex), target(targetIndex), weight(synapticWeight) {}

int Synapse::getSourceIndex() const {
    return source;
}

int Synapse::getTargetIndex() const {
    return target;
}

double Synapse::getWeight() const {
    return weight;
}

void Synapse::setWeight(double newWeight) {
    weight = newWeight;
}
