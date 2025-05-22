#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "Synapse.h"
#include "IntegrateAndFireNeuron.h"

using Catch::Approx;

TEST_CASE("Synapse propagates current correctly", "[Synapse]") {
    auto neuron1 = std::make_unique<IntegrateAndFireNeuron>();
    auto neuron2 = std::make_unique<IntegrateAndFireNeuron>();
    std::vector<std::unique_ptr<Neuron>> neurons;
    neurons.emplace_back(std::move(neuron1));
    neurons.emplace_back(std::move(neuron2));

    double weight = 5.0;
    Synapse syn(0, 1, weight);

    dynamic_cast<IntegrateAndFireNeuron*>(neurons[0].get())->setInputCurrent(100.0);
    neurons[0]->update(1.0);

    REQUIRE(neurons[0]->hasSpiked());

    syn.propagate(neurons);

    double v_before = neurons[1]->getVoltage();
    neurons[1]->update(1.0);
    double v_after = neurons[1]->getVoltage();

    REQUIRE(v_after > v_before);
}

TEST_CASE("Synapse weight can be updated", "[Synapse]") {
    Synapse syn(0, 1, 1.0);
    syn.setWeight(2.5);
    REQUIRE(syn.getWeight() == Approx(2.5));
}

TEST_CASE("Synapse indices are correct", "[Synapse]") {
    Synapse syn(3, 7, 1.0);
    REQUIRE(syn.getSourceIndex() == 3);
    REQUIRE(syn.getTargetIndex() == 7);
}
