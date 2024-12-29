# Class Finder Project

## Folder structure
```
Class Finder Programm/
├── PalaciosAlg.py            # Python implementation
├── GUI.py                    # Python GUI script
├── TestFile.ipynb            # Jupyter Notebook with test matrices
├── CPP-Palacios/             # Folder for C++ implementation
│   ├── main.cpp              # Main program demonstrating usage
│   ├── src/
│       ├── Palacios.cpp      # C++ implementation of the algorithm
├── README.md                 # Documentation for the project
├── dist/                     # Folder for executable files (created by pyinstaller)
│   ├── class_finder          # Executable file for Python GUI

```

This project implements an algorithm to find the exchangeable classes of a Markov chain based on the transition matrix $K$.

## Available Implementations

### 1. Python
- **Files:** `PalaciosAlg.py`, `GUI.py`
- **Description:** 
  - `PalaciosAlg.py` contains the algorithm implementation in Python. It can be further used in other python programs by importing the functions "find_atoms" or "find_classes"
    - `find_atoms`: outputs the sets $A \times B$ for which $\{X_0 \in A\} = \{X_1 \in B\}$. 
    - `find_classes`: outputs the exchangeable classes, i.e. the $I \subset \mathbb{X}$ for which $I$ is an exchangeable class
  - `GUI.py` provides a graphical user interface for the Python implementation.
- **Execution:** There are three ways to execute the 
  1. Open the executable file `class_finder` (no Python installation required).
  2. Alternatively, you can use Python directly:
     ```bash
     python3 GUI.py
     ```
  3. If You wish to make an executable file for the GUI, execute the following command in the terminal:
        ```bash
            ./CreateExeForPalaciosAlgorithm.sh
        ```
        An executable file is then created in the `dist` folder. You can start the program by simply clicking on it.
        You might need to give execution rights to the file by 
        ```bash
            chmod +x CreateExeForPalaciosAlgorithm.sh
        ```

### 2. C++
- **Files:** `Palacios.cpp`, `main.cpp`
- **Description:** 
  - `Palacios.cpp` contains the algorithm implementation in C++. It can be further imported if You wish to create an own 
  - `main.cpp` demonstrates its usage and includes example matrices.


## Notes
- **Matrix Format:** All implementations expect square matrices filled with numbers or fractions.
- **Examples:** You can find test matrices in the C++ and ipynb scripts.

## Contact
For questions or feedback, please contact

- Filip Bojko
- fil.bojko@icloud.com