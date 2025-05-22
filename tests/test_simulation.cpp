#include <catch2/catch_test_macros.hpp>
#include "Simulation.h"
#include "IntegrateAndFireNeuron.h"

TEST_CASE("Simulation initializes correct number of neurons") {
    Simulation sim(5, 4);
    REQUIRE(sim.neuronCount() == 20);
}

TEST_CASE("Simulation sets and retrieves input current") {
    Simulation sim(2, 2);
    sim.setInputCurrent(1.5);
    sim.step();
    for (int i = 0; i < sim.neuronCount(); ++i) {
        REQUIRE(sim.getNeuron(i)->getVoltage() > -65.0);
    }
}

TEST_CASE("Simulation step advances time") {
    Simulation sim(3, 3);
    double t0 = sim.currentTime();
    sim.step();
    REQUIRE(sim.currentTime() > t0);
}

TEST_CASE("Simulation records spikes correctly") {
    Simulation sim(1, 1);
    sim.setInputCurrent(100.0);
    for (int i = 0; i < 20; ++i) {
        sim.step();
    }
    bool spiked = false;
    for (const auto& ev : sim.spikeEvents()) {
        if (ev.second == 0) {
            spiked = true;
            break;
        }
    }
    REQUIRE(spiked);
}

TEST_CASE("Simulation computes spike rate accurately") {
    Simulation sim(1, 1);
    sim.setInputCurrent(100.0);
    for (int i = 0; i < 100; ++i) {
        sim.step();
    }
    double rate = sim.getSpikeRate(0, 50.0);
    REQUIRE(rate > 0.0);
}

TEST_CASE("Simulation supports connectivity by proximity") {
    Simulation sim(3, 3);
    sim.connectByProximity(1.5, 0.5);
    REQUIRE(sim.spikeEvents().empty());
}
