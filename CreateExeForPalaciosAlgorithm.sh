#!/bin/bash

# Name der Python-Datei (passe den Namen an)
PYTHON_SCRIPT="PalaciosAlgorithmGUI.py"

# Überprüfen, ob die Python-Datei existiert
if [ ! -f "$PYTHON_SCRIPT" ]; then
    echo "Error: The file $PYTHON_SCRIPT could not be found."
    exit 1
fi

# Installiere PyInstaller (falls noch nicht vorhanden)
echo "Install PyInstaller..."
pip install --upgrade pyinstaller || { echo "Error: PyInstaller could not be installed."; exit 1; }

# Erstelle die ausführbare Datei
echo "Create an executable file with PyInstaller..."
pyinstaller --onefile "$PYTHON_SCRIPT" || { echo "Error: Could not create an executable file."; exit 1; }

# Ausgabe
echo "An executable file has been created in ./dist/"