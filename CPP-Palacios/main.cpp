#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include "src/Palacios.cpp"
#include <sstream>


using namespace std;

// Function to convert a fractional of the format "enumerator/denominator" into a double 
double fractionToDouble(const string& input) {
    double numerator = 0.0, denominator = 1.0;
    char slash; // For the symbol '/'
    
    // Split the strings into enumerator and denominator 
    stringstream ss(input);
    ss >> numerator >> slash >> denominator;

    // Check if the input format is correct and whether the denominator is greater zero 
    if (ss.fail() || slash != '/' || denominator == 0) {
        throw invalid_argument("Invalid fraction input.");
    }

    return numerator / denominator;
}

// Function for the output of a matrix in the terminal
void printMatrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl; // Line break 
    }
}


vector<vector<double>> inputSquareMatrix() {
    int size;
    while (true) {
        cout << "Enter the size of the square matrix (rows = columns): ";
        cin >> size;

        if (size <= 0) {
            cout << "Invalid size! Size must be greater than 0.\n";
            continue;
        }

        vector<vector<double>> matrix(size, vector<double>(size));

        // Read matrix elements row by row
        for (int i = 0; i < size; ++i) {
            vector<double> row;
            string inputLine;
            string value;

            cout << "Enter " << size << " elements for row " << i + 1 << ", separated by spaces:\n";
            cin.ignore(cin.rdbuf()->in_avail());  // Delete input buffer after the last cin
            getline(cin, inputLine);
            istringstream stream(inputLine);

            while (stream >> value) {
                try {
                    if (value.find('/') != string::npos) {
                        // If the input contains a '/', treat as a fraction
                        row.push_back(fractionToDouble(value));
                    } else {
                        // Otherwise treat as a normal number
                        row.push_back(stod(value));
                    }
                } catch (const invalid_argument& e) {
                    cout << "Invalid input detected: " << value << ". Please enter valid numbers or fractions (e.g., 1/2).\n";
                    row.clear(); // Discard current line
                    break; //  Force new line input
                }
            }

            // Check whether the number of elements in the row is correct
            if (row.size() != size) {
                cout << "Incorrect number of elements in row " << i + 1 << "! You must enter exactly " << size << " elements.\n";
                i--; // Reset line index to enter this line again
            } else {
                matrix[i] = row; // Add row to matrix
            }
        }

        return matrix; // Returns the correctly entered square matrix
    }
}




int main() {
    double h = 0.5; //one half
    double t = 1.0/3.0; //one third
    vector<vector<double>> K_test{
        {0,0,1,0,0,1},
        {1,0,0,0,0,0}, 
        {1,1,0,1,0,0}, 
        {0,0,1,0,0,1},
        {0,1,0,1,0,0},
        {0,0,0,0,1,0}
    }; 

    vector<vector<double>> MusicEx{
        {0,1,0,0,0,0,0,0,0,0}, //0
        {0,0,1,0,0,0,0,0,0,0}, //1
        {0,0,0,1,0,0,0,0,0,0}, //2
        {h,0,0,0,h,0,0,0,0,0}, //3
        {0,0,0,t,0,t,t,0,0,0}, //4
        {0,0,0,0,0,0,h,h,0,0}, //5
        {0,0,0,0,0,0,0,h,h,0}, //6
        {0,0,0,0,0,0,0,0,h,h}, //7
        {0,0,0,0,h,0,0,0,0,h},
        {0,0,0,0,h,h,0,0,0,0}
    };

    vector<vector<double>> ErrorTest{
        {0,1,0,0,0,0,0,0,0,0}, //0
        {0,0,1,0,0,0,0,0,0,0}, //1
        {0,0,0,1,0,0,0,0,0,0}, //2
        {h,0,0,0,h,0,0,0,0,0}, //3
        {0,0,0,t,0,t,t,0,0,0}, //4
        {0,0,0,0,0,0,h,h,0,0}, //5
        {0,0,0,0,0,0,0,h,h,0}, //6
        {0,0,0,0,0,0,0,0,h,h}, //7
        {0,0,0,0,h,0,0,0,0,h},
    };
    cout << "Helloworld" << endl;
    vector<set<pair<int,int>>> Ms = find_classes(K_test);
    vector<set<int>> E = exchangeableClasses(K_test);
    cout << "Helloworld4" << endl;

    printExchangeableClasses(E);
    printVectorOfSets(Ms);
    
    return 0;
}