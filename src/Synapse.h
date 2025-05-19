#pragma once

/**
 * @class Synapse
 * @brief Represents a unidirectional connection from one neuron to another.
 *
 * A Synapse connects two neurons by index in a simulation, and has a weight
 * which determines the strength and type (excitatory/inhibitory) of the connection.
 */
class Synapse {
public:
    /**
     * @brief Constructs a synapse between source and target neurons.
     *
     * @param sourceIndex Index of the presynaptic neuron.
     * @param targetIndex Index of the postsynaptic neuron.
     * @param synapticWeight Synaptic strength. Positive is excitatory, negative is inhibitory.
     */
    Synapse(int sourceIndex, int targetIndex, double synapticWeight);

    /**
     * @brief Gets the index of the source (presynaptic) neuron.
     * @return Index of the source neuron.
     */
    int getSourceIndex() const;

    /**
     * @brief Gets the index of the target (postsynaptic) neuron.
     * @return Index of the target neuron.
     */
    int getTargetIndex() const;

    /**
     * @brief Gets the weight of the synapse.
     * @return The synaptic weight.
     */
    double getWeight() const;

    /**
     * @brief Sets a new synaptic weight.
     * @param newWeight The new synaptic weight.
     */
    void setWeight(double newWeight);

private:
    int source;    ///< Index of the presynaptic neuron.
    int target;    ///< Index of the postsynaptic neuron.
    double weight; ///< Strength of the connection.
};
