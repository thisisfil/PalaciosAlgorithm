import tkinter as tk
from tkinter import messagebox
import ast

from PalaciosAlg import *


# Funktion zum Verarbeiten der Matrix-Eingabe
def process_matrix_input():
    try:
        # Matrix aus dem Eingabefeld auslesen
        matrix_input = matrix_entry.get("1.0", tk.END).strip()
        matrix = ast.literal_eval(matrix_input)  # Parsen der Matrix (sicher)
        
        # Validierung der Matrix
        if not isinstance(matrix, list) or not all(isinstance(row, list) for row in matrix):
            raise ValueError("Die Eingabe ist keine gültige Matrix.")
        if not all(len(row) == len(matrix) for row in matrix):
            raise ValueError("Die Matrix ist nicht quadratisch.")
        
        # Berechnung mit der Funktion find_classes
        result = find_classes(matrix)
        
        # Ergebnis anzeigen
        messagebox.showinfo("Ergebnis", f"Gefundene Klassen: {result}")
    except Exception as e:
        # Fehler anzeigen
        messagebox.showerror("Fehler", f"Ungültige Eingabe: {e}")


if __name__ == "__main__":
    # GUI-Erstellung
    root = tk.Tk()
    root.title("Matrix-Klassenfinder nach Palacios")

    # Beschriftung
    tk.Label(root, text="Geben Sie eine quadratische Matrix ein:").pack(pady=5)

    # Eingabefeld
    matrix_entry = tk.Text(root, height=10, width=50)
    matrix_entry.pack(pady=5)

    # Start-Button
    start_button = tk.Button(root, text="Berechnen", command=process_matrix_input)
    start_button.pack(pady=10)

    # GUI starten
    root.mainloop()