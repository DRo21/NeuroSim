# NeuroSim - Real-Time Neuron Activity Visualizer

**NeuroSim** is a real-time neuronal simulator and voltage visualizer built with modern C++20, Qt 6, and OpenGL. It simulates spiking neuron dynamics using the biologically inspired Izhikevich model and plots membrane potential activity live, providing an intuitive way to understand and debug neural behavior.

---

## 🔬 Features

- ✅ **Biologically accurate spiking neurons** using the **Izhikevich model**  
- 🎨 **Real-time membrane voltage plotting** via **OpenGL**  
- 💬 **Command-line control interface** (`start`, `stop`, `set current <val>`)  
- 🧰 Built with **CMake**, **Qt 6**, and **C++20**  
- 🖼️ Fullscreen **Qt GUI** with clean layout  

---

## 🧠 Neuron Model

This simulator implements the Izhikevich spiking model, known for combining biological realism with computational efficiency:

dv/dt = 0.04v² + 5v + 140 - u + I
du/dt = a(bv - u)


- Parameters: `a = 0.02`, `b = 0.2`, `c = -65`, `d = 8`

---

## 🔧 Build Instructions

### 🛠 Requirements

- CMake 3.16+  
- Qt 6 (tested with 6.5+)  
- C++20 compatible compiler (e.g., GCC 11+, Clang 13+, MSVC 2019+)  

### 💻 Build Steps

```bash
git clone https://github.com/DRo21/NeuroSim.git
cd NeuroSim
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=/path/to/Qt6
make
./NeuroSim
