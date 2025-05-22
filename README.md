# NeuroSim

**NeuroSim** is a real-time spiking neural network simulator and visualizer built in C++20 with Qt 6 and OpenGL. It supports biologically inspired neuron models and interactive visualizations for exploring neural dynamics.

## Features

- **Real-Time Simulation**  
  Simulates neuron dynamics using spiking models like:
  - Izhikevich model
  - Leaky Integrate-and-Fire (LIF)

- **Interactive GUI with Qt 6**
  - **Heatmap View**: Visualizes voltage, spike rate, or spike amplitude.
  - **Trace View**: Live voltage traces for selected neurons.
  - **Raster Plot**: Time vs. spike raster visualization.
  - **Control Panel**: Start/stop simulation, adjust input current, grid size, and more.

- **Modular Architecture**
  - Easily switch between neuron models.
  - Extendable with additional neuron types and visualization widgets.

- **Python Bindings via pybind11**
  - Simulate and access neuron state from Python.

- **Comprehensive Testing**
  - Unit testing with Catch2
  - GUI testing with QtTest

- **Doxygen API Documentation**

## Installation

### Requirements

- CMake ≥ 3.16
- C++20 compiler (GCC, Clang, MSVC)
- Qt 6 (Widgets, OpenGLWidgets, Test modules)
- Python 3 (headers + dev libraries)
- Git (for cloning submodules)

### Build Instructions

```bash
git clone --recurse-submodules https://github.com/DRo21/NeuroSim.git
cd NeuroSim
python3 build_and_setup.py
```

### Run the Simulator

```bash
./NeuroSim
```

## Python Integration

The `neurosim` Python module provides access to the simulation core for datascience purpose:

```python
import neurosim

sim = neurosim.Simulation(10, 10)
sim.step()
print(sim.get_voltage(5))
```

## Testing

### Unit Tests

```bash
./NeuroSimTests
```

### GUI Tests

```bash
ctest --output-on-failure
```

## Documentation

To generate API docs using Doxygen:

```bash
make doc_doxygen
```

Docs will be generated in `docs/html/`.

## License

MIT License — see [LICENSE](LICENSE) file.

## Acknowledgments

NeuroSim uses and integrates:

- [Qt 6](https://www.qt.io/)
- [pybind11](https://github.com/pybind/pybind11)
- [Catch2](https://github.com/catchorg/Catch2)

---

📁 GitHub: [https://github.com/DRo21/NeuroSim/](https://github.com/DRo21/NeuroSim/)
