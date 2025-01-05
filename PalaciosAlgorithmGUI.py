import tkinter as tk
from tkinter import messagebox
import ast

from PalaciosAlg import *


# Function for processing the matrix input 
def process_matrix_input():
    try:
        # Read the matrix from the input field 
        matrix_input = matrix_entry.get("1.0", tk.END).strip()
        matrix = ast.literal_eval(matrix_input)  # Parse the Matrix
        
        # Validate the matrix 
        if not isinstance(matrix, list) or not all(isinstance(row, list) for row in matrix):
            raise ValueError("Your input is not a valid matrix.")
        if not all(len(row) == len(matrix) for row in matrix):
            raise ValueError("Your matrix is not quadratic.")
        
        # Calculate the result of find_classes 
        result = find_classes(matrix)
        
        # Show the results 
        messagebox.showinfo("Result", f"Exchangeable classes: {result}")
    except Exception as e:
        # Show error messages
        messagebox.showerror("Error", f"Invalid input: {e}")


if __name__ == "__main__":
    # create the GUI
    root = tk.Tk()
    root.title("Exchangeable class finder by Palacios' algorithm")

    # Labeling
    tk.Label(root, text="Enter a quadratic matrix  as a list of lists, \n i.e. in the format \n [[row 1], \n [row 2], \n ...]:").pack(pady=5)

    # input field
    matrix_entry = tk.Text(root, height=10, width=50)
    matrix_entry.pack(pady=5)

    # Start button
    start_button = tk.Button(root, text="Calculate", command=process_matrix_input)
    start_button.pack(pady=10)

    # start the GUI
    root.mainloop()