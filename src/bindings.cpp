/**
 * @file bindings.cpp
 * @brief Python bindings for the NeuroSim core using pybind11.
 * @author Dario Romandini
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <memory>

#include "Neuron.h"
#include "IntegrateAndFireNeuron.h"
#include "Synapse.h"
#include "Simulation.h"

namespace py = pybind11;

PYBIND11_MODULE(neurosim, m) {
    m.doc() = "NeuroSim: Python interface for spiking neural network simulation";

    py::class_<Neuron, std::shared_ptr<Neuron>>(m, "Neuron")
        .def("update", &Neuron::update, py::arg("dt"))
        .def("receive_synaptic_current", &Neuron::receiveSynapticCurrent, py::arg("i_syn"))
        .def("has_spiked", &Neuron::hasSpiked)
        .def("last_spike_time", &Neuron::lastSpikeTime)
        .def("get_voltage", &Neuron::getVoltage);

    py::class_<IntegrateAndFireNeuron, Neuron, std::shared_ptr<IntegrateAndFireNeuron>>(m, "IntegrateAndFireNeuron")
        .def(py::init<double, double, double, double>(),
             py::arg("v_rest") = -65.0,
             py::arg("v_thresh") = -50.0,
             py::arg("tau") = 20.0,
             py::arg("reset_v") = -65.0);

    py::class_<Synapse>(m, "Synapse")
        .def(py::init<int, int, double>(), py::arg("src"), py::arg("dst"), py::arg("weight"))
        .def("src", &Synapse::src)
        .def("dst", &Synapse::dst)
        .def("weight", &Synapse::weight);

    py::class_<Simulation>(m, "Simulation")
        .def(py::init<int, int, double>(), py::arg("nx"), py::arg("ny"), py::arg("dt") = 0.1)
        .def("step", &Simulation::step)
        .def("connect_random", &Simulation::connectRandom, py::arg("p"), py::arg("weight"))
        .def("connect_by_proximity", &Simulation::connectByProximity, py::arg("radius"), py::arg("weight"))
        .def("neuron_count", &Simulation::neuronCount)
        .def("nx", &Simulation::nx)
        .def("ny", &Simulation::ny)
        .def("spike_events", &Simulation::spikeEvents, py::return_value_policy::reference_internal)
        .def("get_spike_rate", &Simulation::getSpikeRate, py::arg("neuron_index"), py::arg("window_ms"))
        .def("get_spike_amplitude", &Simulation::getSpikeAmplitude, py::arg("neuron_index"), py::arg("window_ms"))
        .def("get_voltage",
             [](Simulation& s, int idx) {
                 return s.getNeuron(idx)->getVoltage();
             },
             py::arg("neuron_index"));
}
