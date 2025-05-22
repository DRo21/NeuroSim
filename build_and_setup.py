import os
import sys
import subprocess
import platform
import shutil

def run(cmd, shell=False):
    print(f"> {' '.join(cmd) if isinstance(cmd, list) else cmd}")
    result = subprocess.run(cmd, shell=shell)
    if result.returncode != 0:
        print(f"Command failed with exit code {result.returncode}: {cmd}")
        sys.exit(result.returncode)

def create_venv(venv_path):
    if not os.path.exists(venv_path):
        print(f"Creating virtual environment at {venv_path}...")
        run([sys.executable, "-m", "venv", venv_path])
    else:
        print(f"Virtual environment already exists at {venv_path}.")

def install_packages(venv_path, packages):
    print("Installing Python packages...")
    if platform.system() == "Windows":
        pip_executable = os.path.join(venv_path, "Scripts", "pip.exe")
    else:
        pip_executable = os.path.join(venv_path, "bin", "pip")

    run([pip_executable, "install", "--upgrade", "pip"])
    run([pip_executable, "install"] + packages)

def activate_venv_cmd(venv_path):
    if platform.system() == "Windows":
        activate_path = os.path.join(venv_path, "Scripts", "Activate.ps1")
        print(f"To activate the virtual environment, run in PowerShell:\n  {activate_path}")
    else:
        activate_path = os.path.join(venv_path, "bin", "activate")
        print(f"To activate the virtual environment, run:\n  source {activate_path}")

def main():
    print(f"Detected OS: {platform.system()}")

    # Create build directory
    build_dir = "build"
    if not os.path.exists(build_dir):
        print(f"Creating build directory: {build_dir}")
        os.mkdir(build_dir)
    else:
        print(f"Build directory '{build_dir}' already exists.")

    # Run CMake configure and build
    cmake_cmd = ["cmake", ".."]
    build_cmd = ["cmake", "--build", "."]

    if platform.system() == "Windows":
        cmake_cmd += ["-G", "Visual Studio 17 2022"]
        pass

    # Change directory into build
    os.chdir(build_dir)

    print("Configuring project with CMake...")
    run(cmake_cmd)

    print("Building project with CMake...")
    run(build_cmd)

    # Back to project root
    os.chdir("..")

    # Setup Python virtual environment
    venv_path = "neurosim-venv"
    create_venv(venv_path)

    # Install required Python packages
    required_packages = ["matplotlib", "numpy", "jupyter", "pandas"]
    install_packages(venv_path, required_packages)

    activate_venv_cmd(venv_path)

    print("\nBuild and setup complete! You can now run your project.")

if __name__ == "__main__":
    main()
