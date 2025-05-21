/**
 * @file bindings.cpp
 * @brief Python bindings for the NeuroSim core using pybind11.
 *
 * Exposes the spiking neural network simulation engine to Python,
 * including neuron models, synapses, and network simulation logic.
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

    // ----------------------------------------------------------------------
    // Bind abstract base class Neuron
    // ----------------------------------------------------------------------
    py::class_<Neuron, std::shared_ptr<Neuron>>(m, "Neuron")
        .def("update", &Neuron::update,
             py::arg("dt"),
             "Advance the neuron's state by a time step (ms).")
        .def("receive_synaptic_current", &Neuron::receiveSynapticCurrent,
             py::arg("i_syn"),
             "Inject synaptic current (nA).")
        .def("has_spiked", &Neuron::hasSpiked,
             "Check if the neuron spiked in the last update.")
        .def("last_spike_time", &Neuron::lastSpikeTime,
             "Get the time of the last spike (ms).")
        .def("get_voltage", &Neuron::getVoltage,
             "Get the current membrane potential (mV).");

    // ----------------------------------------------------------------------
    // Bind concrete subclass IntegrateAndFireNeuron
    // ----------------------------------------------------------------------
    py::class_<IntegrateAndFireNeuron, Neuron, std::shared_ptr<IntegrateAndFireNeuron>>(m, "IntegrateAndFireNeuron")
        .def(py::init<double, double, double, double>(),
             py::arg("v_rest")   = -65.0,
             py::arg("v_thresh") = -50.0,
             py::arg("tau")      = 20.0,
             py::arg("reset_v")  = -65.0,
             "Construct a leaky integrate-and-fire neuron with optional parameters.");

    // ----------------------------------------------------------------------
    // Bind Synapse
    // ----------------------------------------------------------------------
    py::class_<Synapse>(m, "Synapse")
        .def(py::init<int, int, double>(),
             py::arg("src"), py::arg("dst"), py::arg("weight"),
             "Create a synapse from source to target with specified weight.")
        .def("src", &Synapse::src, "Get the source neuron index.")
        .def("dst", &Synapse::dst, "Get the target neuron index.")
        .def("weight", &Synapse::weight, "Get the synaptic weight (nA).");

    // ----------------------------------------------------------------------
    // Bind Simulation
    // ----------------------------------------------------------------------
    py::class_<Simulation>(m, "Simulation")
        .def(py::init<int, int, double>(),
             py::arg("nx"), py::arg("ny"), py::arg("dt") = 0.1,
             "Create a simulation grid with dimensions nx×ny and time step dt (ms).")
        .def("step", &Simulation::step,
             "Advance the simulation by one time step.")
        .def("connect_random", &Simulation::connectRandom,
             py::arg("p"), py::arg("weight"),
             "Randomly connect neurons with probability p and specified weight.")
        .def("connect_by_proximity", &Simulation::connectByProximity,
             py::arg("radius"), py::arg("weight"),
             "Connect neurons within radius (grid units) using given weight.")
        .def("neuron_count", &Simulation::neuronCount,
             "Get the total number of neurons.")
        .def("nx", &Simulation::nx, "Get the number of columns in the grid.")
        .def("ny", &Simulation::ny, "Get the number of rows in the grid.")
        .def("spike_events", &Simulation::spikeEvents,
             py::return_value_policy::reference_internal,
             "Access the list of spike events as (time_ms, neuron_index) tuples.")
        .def("get_spike_rate", &Simulation::getSpikeRate,
             py::arg("neuron_index"), py::arg("window_ms"),
             "Get the firing rate (Hz) over the last window_ms.")
        .def("get_spike_amplitude", &Simulation::getSpikeAmplitude,
             py::arg("neuron_index"), py::arg("window_ms"),
             "Estimate the spike amplitude (mV) over the last window.")
        .def("get_voltage", [](Simulation& s, int idx) {
                return s.getNeuron(idx)->getVoltage();
             },
             py::arg("neuron_index"),
             "Get the current voltage of the given neuron.");
}
