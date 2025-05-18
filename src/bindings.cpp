/**
 * @file bindings.cpp
 * @brief Python bindings for the NeuroSim simulation and neuron model using pybind11.
 *
 * This module exposes the core C++ classes `Neuron` and `Simulation` to Python for
 * data science, analysis, and visualization workflows using Jupyter and matplotlib.
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Simulation.h"
#include "Neuron.h"

namespace py = pybind11;

/**
 * @brief Python module definition for `neurosim`.
 *
 * Exposes the C++ classes:
 *   - `Neuron`: Single Izhikevich neuron
 *   - `Simulation`: Manages a population of neurons
 *
 * @param m Python module object for `neurosim`
 */
PYBIND11_MODULE(neurosim, m) {
    m.doc() = "Python bindings for neuron simulation using pybind11";

    /**
     * @brief Bind the Neuron class.
     */
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
             "Get the current membrane voltage of the neuron.");

    /**
     * @brief Bind the Simulation class.
     */
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
             "Return the index of the currently selected neuron.");
}
