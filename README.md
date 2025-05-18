# NeuroSim - Real-Time Neuron Activity Visualizer

**NeuroSim** is a real-time neuronal simulator and voltage visualizer built with modern C++20, Qt 6, and OpenGL. It simulates spiking neuron dynamics using the biologically inspired Izhikevich model and plots membrane potential activity live, providing an intuitive way to understand and debug neural behavior. In addition to the voltage trace of a single neuron, NeuroSim displays a small 3 × 3 heatmap that reflects the voltage of all nine neurons in real time.

Additionally, **NeuroSim provides Python bindings** using pybind11, allowing you to run simulations, extract data, and visualize neuron dynamics within Python scripts or Jupyter notebooks.

---

## 🔬 Features

- ✅ **Biologically accurate spiking neurons** using the **Izhikevich model**  
- 🎨 **Real-time membrane voltage plotting** via **OpenGL**  
- 🔥 **3 × 3 heatmap** showing normalized voltages of nine neurons  
- 💬 **Command-line control interface** (`start`, `stop`, `set current <val>`, `select neuron <index>`)  
- 🧰 Built with **CMake**, **Qt 6**, and **C++20**  
- 🖼️ Fullscreen **Qt GUI** with clean layout  
- 🐍 **Python API** bindings for scripting and integration with scientific Python stack (matplotlib, numpy)  
- 📓 Example Python demos and Jupyter notebooks included for interactive exploration  

---

## 🧠 Neuron Model

This simulator implements the Izhikevich spiking model, known for combining biological realism with computational efficiency:

dv/dt = 0.04v² + 5v + 140 - u + I du/dt = a(bv - u)

- Parameters:  
  - \(a = 0.02\)  
  - \(b = 0.2\)  
  - \(c = -65\)  
  - \(d = 8\)

Nine neurons (arranged conceptually in a 3 × 3 grid) are simulated simultaneously. Each neuron’s voltage is displayed in the heatmap, and the left panel shows the voltage trace of the “selected” neuron (index 0 by default).

---

## 🔧 Build and Setup Instructions

### 🛠 Requirements

- CMake 3.16+  
- Qt 6 (tested with 6.5+)  
- C++20-compatible compiler (GCC 11+, Clang 13+, MSVC 2019+)  
- Python 3.8+ (for Python API and demos)  
- `python3-venv` package (for creating Python virtual environments)  

---

### ⚡ Automated Build and Setup Script (`build_and_setup.py`)

To streamline installation, building, and environment setup across **Windows**, **Linux**, and **macOS**, use the provided Python script `build_and_setup.py`. This script will:

- Detect your OS  
- Create a `build/` directory if it doesn't exist  
- Run CMake configuration and build the C++ executable and Python bindings  
- Create a Python virtual environment (`neurosim-venv`) if missing  
- Install Python dependencies (`matplotlib`, `numpy`, `jupyter`) inside the venv  
- Display instructions to activate the virtual environment  

---

### 🚀 How to Use

1. Make sure Python 3 is installed and accessible as `python3` or `python`.  
2. Place the `build_and_setup.py` script at the root of the NeuroSim repository.  
3. Open a terminal (Linux/macOS) or PowerShell/CMD (Windows) in the NeuroSim root folder.  
4. Run the script:

```bash
python3 build_and_setup.py
# Or on some Windows setups:
python build_and_setup.py
```

---

## 🐍 Activating the Python Virtual Environment

After the script finishes, activate the virtual environment:

- **Linux/macOS:**

```bash
source neurosim-venv/bin/activate
```

- **Windows PowerShell:**

```ps1
.\neurosim-venv\Scripts\Activate.ps1
```

- **Windows CMD:**

```cmd
.\neurosim-venv\Scripts\activate.bat
```

## 🐍 Running Python Demos

Make sure your `PYTHONPATH` environment variable includes the build directory, so Python can find the compiled `neurosim` module.

### Linux/macOS:

```bash
export PYTHONPATH=$(pwd)/build
```

- **Windows PowerShell:**

```ps1
$env:PYTHONPATH = "$PWD\build"
```

- **Windows CMD:**

```cmd
set PYTHONPATH=%CD%\build
```

Then you can start Jupyter Notebook e.g.:

```bash
jupyter notebook
```