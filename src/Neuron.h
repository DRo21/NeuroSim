#pragma once

/**
 * @brief Represents a single neuron based on the Izhikevich model.
 */
class Neuron {
public:
    /**
     * @brief Constructs a Neuron with given parameters.
     * 
     * @param a Recovery time scale.
     * @param b Sensitivity of recovery variable to voltage.
     * @param c After-spike reset value of membrane potential.
     * @param d After-spike reset of recovery variable.
     */
    Neuron(double a = 0.02, double b = 0.2, double c = -65.0, double d = 8.0);

    /**
     * @brief Updates the neuron's state given the input current and time step.
     * 
     * @param inputCurrent External current input.
     * @param dt Time step for numerical integration.
     */
    void update(double inputCurrent, double dt);

    /**
     * @brief Checks if the neuron fired (spiked) during the last update.
     * 
     * @return true if the neuron fired.
     * @return false otherwise.
     */
    bool fired() const;

    /**
     * @brief Gets the current membrane voltage.
     * 
     * @return Current voltage (mV).
     */
    double getVoltage() const;

private:
    double v;       ///< Membrane potential (voltage).
    double u;       ///< Recovery variable.
    double a, b;    ///< Neuron model parameters.
    double c, d;    ///< Reset values after spike.
    bool spike;     ///< Indicates whether the neuron fired.
};
