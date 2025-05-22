/**
 * @file Simulation.cpp
 * @brief Implements Simulation class controlling a grid of spiking neurons.
 * @author Dario Romandini
 */

#include "Simulation.h"
#include "IntegrateAndFireNeuron.h"
#include <random>
#include <cmath>
#include <algorithm>

Simulation::Simulation(int nx, int ny, double dt)
    : nx_(nx), ny_(ny), dt_(dt), currentTime_(0.0)
{
    initializeNeurons();
}

void Simulation::initializeNeurons()
{
    neurons_.clear();
    neurons_.reserve(nx_ * ny_);
    for (int i = 0; i < nx_ * ny_; ++i) {
        neurons_.emplace_back(std::make_unique<IntegrateAndFireNeuron>());
    }

    synapses_.clear();
    events_.clear();
    currentTime_ = 0.0;
}

void Simulation::connectRandom(double probability, double weight)
{
    std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<> dist(0.0, 1.0);

    int N = neuronCount();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i != j && dist(gen) < probability) {
                synapses_.emplace_back(i, j, weight);
            }
        }
    }
}

void Simulation::connectByProximity(double radius, double weight)
{
    for (int y1 = 0; y1 < ny_; ++y1) {
        for (int x1 = 0; x1 < nx_; ++x1) {
            int i = index(x1, y1);
            for (int y2 = 0; y2 < ny_; ++y2) {
                for (int x2 = 0; x2 < nx_; ++x2) {
                    int j = index(x2, y2);
                    if (i != j) {
                        double dx = x1 - x2;
                        double dy = y1 - y2;
                        if (std::sqrt(dx * dx + dy * dy) <= radius) {
                            synapses_.emplace_back(i, j, weight);
                        }
                    }
                }
            }
        }
    }
}

void Simulation::step()
{
    for (auto& neuron : neurons_) {
        neuron->receiveSynapticCurrent(globalInputCurrent_);
        neuron->update(dt_);
    }

    for (auto& syn : synapses_) {
        syn.propagate(neurons_);
    }

    for (int i = 0; i < neuronCount(); ++i) {
        if (neurons_[i]->hasSpiked()) {
            events_.emplace_back(currentTime_, i);
        }
    }

    currentTime_ += dt_;
}

int Simulation::neuronCount() const { return static_cast<int>(neurons_.size()); }
int Simulation::nx() const { return nx_; }
int Simulation::ny() const { return ny_; }
double Simulation::currentTime() const { return currentTime_; }

Neuron* Simulation::getNeuron(int idx) const
{
    return neurons_.at(idx).get();
}

const std::vector<std::pair<double, int>>& Simulation::spikeEvents() const
{
    return events_;
}

double Simulation::getSpikeRate(int idx, double window_ms) const
{
    double startTime = std::max(0.0, currentTime_ - window_ms);
    int count = std::count_if(events_.begin(), events_.end(),
        [=](const auto& ev) {
            return ev.second == idx && ev.first >= startTime && ev.first <= currentTime_;
        });

    return (window_ms > 0.0) ? (count * 1000.0 / window_ms) : 0.0;
}

double Simulation::getSpikeAmplitude(int idx, double /*window_ms*/) const
{
    return neurons_.at(idx)->getVoltage();
}

void Simulation::setInputCurrent(double current)
{
    globalInputCurrent_ = current;
}

void Simulation::setSelectedNeuron(int index)
{
    selectedNeuronIndex_ = index;
}
