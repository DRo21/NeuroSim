/**
 * @file Synapse.h
 * @brief Defines the Synapse class that connects two neurons in the network model. 
 *        Delivers current based on spiking activity of the source neuron.
 * @author Dario Romandini
 */

#ifndef SYNAPSE_H
#define SYNAPSE_H

#include <memory>
#include <vector>
#include "Neuron.h"

/**
 * @class Synapse
 * @brief Models a directed synapse between two neurons.
 *
 * Delivers a fixed-weighted current to the destination neuron if the source neuron spikes.
 */
class Synapse
{
public:
    /**
     * @brief Construct a synapse between two neurons.
     * @param srcIndex Index of the source neuron.
     * @param dstIndex Index of the destination neuron.
     * @param weight Synaptic weight (nA).
     */
    Synapse(int srcIndex, int dstIndex, double weight);

    /**
     * @brief Propagate a spike from source to destination if source neuron has spiked.
     * @param neurons Vector of neuron pointers.
     */
    void propagate(const std::vector<std::unique_ptr<Neuron>>& neurons) const;

    /** @return Index of the source neuron. */
    int src() const;

    /** @return Index of the destination neuron. */
    int dst() const;

    /** @return Synaptic weight in nanoamperes (nA). */
    double weight() const;

    /** @brief Set the synaptic weight. */
    void setWeight(double w);

    // Accessors for unit test compatibility
    double getWeight() const { return weight(); }
    int getSourceIndex() const { return src(); }
    int getTargetIndex() const { return dst(); }

private:
    int src_;         ///< Source neuron index
    int dst_;         ///< Destination neuron index
    double weight_;   ///< Synaptic weight (nA)
};

#endif // SYNAPSE_H
