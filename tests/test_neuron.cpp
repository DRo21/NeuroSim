#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "IntegrateAndFireNeuron.h"

using Catch::Approx;

TEST_CASE("IntegrateAndFireNeuron spikes with sufficient input") {
    IntegrateAndFireNeuron neuron;
    neuron.setInputCurrent(100.0);
    for (int i = 0; i < 10; ++i) {
        neuron.update(0.1);
    }
    REQUIRE(neuron.hasSpiked());
}

TEST_CASE("IntegrateAndFireNeuron does not spike with subthreshold input") {
    IntegrateAndFireNeuron neuron;
    neuron.setInputCurrent(0.5);
    for (int i = 0; i < 10; ++i) {
        neuron.update(0.1);
    }
    REQUIRE_FALSE(neuron.hasSpiked());
}

TEST_CASE("IntegrateAndFireNeuron resets after spike") {
    IntegrateAndFireNeuron neuron;
    neuron.setInputCurrent(100.0);
    for (int i = 0; i < 10; ++i) {
        neuron.update(0.1);
    }
    REQUIRE(neuron.getVoltage() < 0.0);
}

TEST_CASE("IntegrateAndFireNeuron accumulates synaptic current") {
    IntegrateAndFireNeuron neuron;
    neuron.receiveSynapticCurrent(1.0);
    neuron.setInputCurrent(0.0);
    neuron.update(0.1);
    REQUIRE(neuron.getVoltage() > -65.0);
}

TEST_CASE("IntegrateAndFireNeuron voltage evolves as expected") {
    IntegrateAndFireNeuron neuron;
    double initial = neuron.getVoltage();
    neuron.setInputCurrent(2.0);
    neuron.update(0.1);
    REQUIRE(neuron.getVoltage() != Catch::Approx(initial).margin(0.01));
}
