# NeuroSim - Real-Time Neuron Activity Visualizer

**NeuroSim** is a real-time neuronal simulator and voltage visualizer built with modern C++20, Qt 6, and OpenGL. It simulates spiking neuron dynamics using the biologically inspired Izhikevich model and plots membrane potential activity live, providing an intuitive way to understand and debug neural behavior. In addition to the voltage trace of a single neuron, NeuroSim displays a small 3 × 3 heatmap that reflects the voltage of all nine neurons in real time.

---

## 🔬 Features

- ✅ **Biologically accurate spiking neurons** using the **Izhikevich model**  
- 🎨 **Real-time membrane voltage plotting** via **OpenGL**  
- 🔥 **3 × 3 heatmap** showing normalized voltages of nine neurons  
- 💬 **Command-line control interface** (`start`, `stop`, `set current <val>`)  
- 🧰 Built with **CMake**, **Qt 6**, and **C++20**  
- 🖼️ Fullscreen **Qt GUI** with clean layout  

---

## 🧠 Neuron Model

This simulator implements the Izhikevich spiking model, known for combining biological realism with computational efficiency:

\[
\begin{aligned}
\frac{dv}{dt} &= 0.04\,v^2 + 5\,v + 140 - u + I, \\
\frac{du}{dt} &= a\,(b\,v - u).
\end{aligned}
\]

- Parameters:  
  - \(a = 0.02\)  
  - \(b = 0.2\)  
  - \(c = -65\)  
  - \(d = 8\)

Nine neurons (arranged conceptually in a 3 × 3 grid) are simulated simultaneously. Each neuron’s voltage is displayed in the heatmap, and the left panel shows the voltage trace of the “selected” neuron (index 0 by default).

---

## 🔧 Build Instructions

### 🛠 Requirements

- CMake 3.16+  
- Qt 6 (tested with 6.5+)  
- C++20-compatible compiler (e.g., GCC 11+, Clang 13+, MSVC 2019+)  

### 💻 Build Steps

```bash
git clone https://github.com/DRo21/NeuroSim.git
cd NeuroSim
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=/path/to/Qt6
make
./NeuroSim
