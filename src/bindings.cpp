/**
 * @file bindings.cpp
 * @brief Python bindings for the NeuroSim simulation, neurons, and synapses using pybind11.
 *
 * This module exposes the core C++ classes:
 *   - Neuron: Single Izhikevich neuron
 *   - Synapse: Connection between neurons
 *   - Simulation: Manages a network of neurons and their interactions
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Neuron.h"
#include "Synapse.h"
#include "Simulation.h"

namespace py = pybind11;

/**
 * @brief Python module definition for `neurosim`.
 *
 * This module allows Python users to simulate spiking neural networks with custom
 * neuron models and synaptic connections.
 *
 * @param m Python module object for `neurosim`
 */
PYBIND11_MODULE(neurosim, m) {
    m.doc() = "Python bindings for spiking neuron simulation using pybind11";

    // Bind Neuron class
    py::class_<Neuron>(m, "Neuron")
        .def(py::init<double, double, double, double>(),
             py::arg("a") = 0.02, py::arg("b") = 0.2,
             py::arg("c") = -65.0, py::arg("d") = 8.0,
             "Construct a neuron with optional Izhikevich parameters.")
        .def("update", &Neuron::update,
             py::arg("inputCurrent"), py::arg("dt"),
             "Update the neuron's state using the input current and time step.")
        .def("fired", &Neuron::fired,
             "Check whether the neuron fired during the last update.")
        .def("get_voltage", &Neuron::getVoltage,
             "Get the current membrane voltage of the neuron.")
        .def("receive_synaptic_input", &Neuron::receiveSynapticInput,
             py::arg("current"),
             "Buffer synaptic input current to be applied on the next update.");

    // Bind Synapse class
    py::class_<Synapse>(m, "Synapse")
        .def(py::init<int, int, double>(),
             py::arg("source"), py::arg("target"), py::arg("weight"),
             "Create a synapse between source and target neuron indices with a specified weight.")
        .def("get_source", &Synapse::getSourceIndex,
             "Get the source (presynaptic) neuron index.")
        .def("get_target", &Synapse::getTargetIndex,
             "Get the target (postsynaptic) neuron index.")
        .def("get_weight", &Synapse::getWeight,
             "Get the current synaptic weight.")
        .def("set_weight", &Synapse::setWeight,
             py::arg("weight"),
             "Set a new synaptic weight.");

    // Bind Simulation class
    py::class_<Simulation>(m, "Simulation")
        .def(py::init<int>(), py::arg("neuronCount"),
             "Construct a simulation with the given number of neurons.")
        .def("step", &Simulation::step,
             py::arg("dt"),
             "Advance the simulation by one time step (dt).")
        .def("neurons", &Simulation::neurons,
             py::return_value_policy::reference_internal,
             "Access the list of neurons in the simulation.")
        .def("set_input_current", &Simulation::setInputCurrent,
             py::arg("current"),
             "Set the external input current for all neurons.")
        .def("get_input_current", &Simulation::getInputCurrent,
             "Get the current value of the external input current.")
        .def("get_voltage_grid", &Simulation::getVoltageGrid,
             py::arg("width"), py::arg("height"),
             "Retrieve a flattened grid of normalized voltages for visualization.")
        .def("set_selected_neuron", &Simulation::setSelectedNeuron,
             py::arg("index"),
             "Select a neuron for detailed tracking or plotting.")
        .def("get_selected_neuron", &Simulation::getSelectedNeuron,
             "Return the index of the currently selected neuron.")
        .def("add_synapse", &Simulation::addSynapse,
             py::arg("source"), py::arg("target"), py::arg("weight"),
             "Add a synaptic connection from source to target with specified weight.")
        .def("clear_synapses", &Simulation::clearSynapses,
             "Remove all existing synaptic connections.");
}
