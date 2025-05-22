// Synapse.h
#ifndef SYNAPSE_H
#define SYNAPSE_H

#include <memory>
#include <vector>
#include "Neuron.h"

/**
 * @brief Models a directed synapse between two neurons.
 *
 * Supports excitatory or inhibitory weights.
 * Open for extension: you can subclass for more complex synapse models
 * (e.g. with delays, plasticity) without modifying this interface.
 */
class Synapse
{
public:
    /**
     * @brief Construct a synapse.
     * @param srcIndex Index of source neuron in the network array.
     * @param dstIndex Index of destination neuron in the network array.
     * @param weight   Synaptic weight (current, nA) delivered on spike.
     */
    Synapse(int srcIndex, int dstIndex, double weight);

    /**
     * @brief Propagate a spike event through this synapse.
     *
     * If the source neuron has just spiked, delivers synaptic current
     * to the destination neuron.
     *
     * @param neurons Vector of neuron pointers comprising the network.
     */
    void propagate(const std::vector<std::unique_ptr<Neuron>>& neurons) const;

    /** @return Index of the source neuron. */
    int src() const;

    /** @return Index of the destination neuron. */
    int dst() const;

    /** @return Synaptic weight (nA). */
    double weight() const;

    /** @brief Set synaptic weight. */
    void setWeight(double w);

    // Synonym methods for compatibility with tests
    double getWeight() const { return weight(); }
    int getSourceIndex() const { return src(); }
    int getTargetIndex() const { return dst(); }

private:
    int    src_;     ///< Source neuron index
    int    dst_;     ///< Destination neuron index
    double weight_;  ///< Synaptic weight (nA)
};

#endif // SYNAPSE_H
