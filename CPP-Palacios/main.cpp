#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include "src/Palacios.cpp"
#include <sstream>


using namespace std;

// Funktion zum Konvertieren eines Bruchs im Format "Zähler/Nenner" in double
double fractionToDouble(const string& input) {
    double numerator = 0.0, denominator = 1.0;
    char slash; // Für das Zeichen '/'
    
    // Aufteilen des Strings in Zähler und Nenner
    stringstream ss(input);
    ss >> numerator >> slash >> denominator;

    // Überprüfen, ob das Eingabeformat korrekt ist und ob der Nenner nicht 0 ist
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
        cout << endl; // Zeilenumbruch nach jeder Zeile
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

        // Matrixelemente zeilenweise einlesen
        for (int i = 0; i < size; ++i) {
            vector<double> row;
            string inputLine;
            string value;

            cout << "Enter " << size << " elements for row " << i + 1 << ", separated by spaces:\n";
            cin.ignore(cin.rdbuf()->in_avail());  // Eingabepuffer nach dem letzten cin löschen
            getline(cin, inputLine);
            istringstream stream(inputLine);

            while (stream >> value) {
                try {
                    if (value.find('/') != string::npos) {
                        // Falls die Eingabe einen '/' enthält, als Bruch behandeln
                        row.push_back(fractionToDouble(value));
                    } else {
                        // Ansonsten als normale Zahl behandeln
                        row.push_back(stod(value));
                    }
                } catch (const invalid_argument& e) {
                    cout << "Invalid input detected: " << value << ". Please enter valid numbers or fractions (e.g., 1/2).\n";
                    row.clear(); // Aktuelle Zeile verwerfen
                    break; // Neue Zeileingabe erzwingen
                }
            }

            // Überprüfung, ob die Anzahl der Elemente in der Zeile korrekt ist
            if (row.size() != size) {
                cout << "Incorrect number of elements in row " << i + 1 << "! You must enter exactly " << size << " elements.\n";
                i--; // Zeilenindex zurücksetzen, um diese Zeile erneut einzugeben
            } else {
                matrix[i] = row; // Zeile zur Matrix hinzufügen
            }
        }

        return matrix; // Rückgabe der korrekt eingegebenen quadratischen Matrix
    }
}







/*
// Funktion zum Einlesen der Matrix vom Nutzer mit Überprüfung
vector<vector<double>> getMatrixFromUser() {
    int numRows;
    bool inputValid = false;
    vector<vector<double>> matrix;

    while (!inputValid) {
        try {
            cout << "Enter the number of rows (and columns) of the matrix (matrix must be square): ";
            cin >> numRows;

            if (numRows <= 0) {
                throw invalid_argument("The number of rows and columns must be positive.");
            }

            matrix.clear();  // Matrix leeren, falls der Nutzer eine falsche Eingabe gemacht hat
            cout << "Enter the matrix values row by row. The input must be in a double format:" << endl;

            // Eingabe für jede Zeile
            for (int i = 0; i < numRows; i++) {
                vector<double> row;
                string rowInput;
                cout << "Enter " << numRows << " values for row " << i + 1 << " (separated by spaces):" << endl;
                
                cin.ignore(); // Eingabepuffer löschen, um Zeilen als Ganzes einzulesen
                getline(cin, rowInput); // Ganze Zeile einlesen

                // Teile die Zeile in einzelne Eingaben auf
                stringstream ss(rowInput);
                string value;
                int count = 0;

                while (ss >> value) {
                    count++;
                    if (count > numRows) {
                        throw invalid_argument("Too many values in a row.");
                    }

                    // Versuche, die Eingabe als Bruch oder Dezimalzahl zu interpretieren
                    if (value.find('/') != string::npos) {
                        row.push_back(fractionToDouble(value));
                    } else {
                        row.push_back(stod(value)); // Konvertiert den String in double
                    }
                }

                if (count < numRows) {
                    throw invalid_argument("Not enough values in the row.");
                }

                // Zeile zur Matrix hinzufügen
                matrix.push_back(row);
            }

            // Wenn die Matrix korrekt eingegeben wurde, ist inputValid = true
            inputValid = true;

        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            cout << "Please try again. Make sure the matrix is square and the inputs are valid." << endl;
            matrix.clear(); // Matrix zurücksetzen
            cin.clear(); // Eingabefehler löschen
        }
    }

    return matrix;
}

*/


/*
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
    //cout << "Hello World" << endl;
    vector<set<pair<int,int>>> Ms = find_classes(K_test);
    vector<set<int>> E = exchangeableClasses(K_test);

    vector<set<pair<int,int>>> M_Music = find_classes(MusicEx);
    vector<set<int>> E_Music = exchangeableClasses(MusicEx);
    //vector<set<int>> Error_Test = exchangeableClasses(ErrorTest);


    //printVectorOfSets(M_Music);
    //printExchangeableClasses(E_Music);
    //printExchangeableClasses(Error_Test);

    try {
        // Matrix vom Nutzer einlesen
        //vector<vector<double>> matrix = getMatrixFromUser();
        vector<vector<double>> matrix = inputSquareMatrix();

        // Aufruf der Funktion find_classes
        vector<set<pair<int,int>>> pre_result = find_classes(matrix);
        vector<set<int>> result = exchangeableClasses(matrix);

        // Ergebnis ausgeben (hier nur ein Platzhalter für deine find_classes Logik)
        cout << "The matrix was processed successfully." << endl;
        cout << "The exchangeable classes of the transition matrix are given by:" << endl;
        printExchangeableClasses(result);
        //printVectorOfSets(pre_result);
        printMatrix(matrix);

    } catch (const invalid_argument& e) {
        // Fehlerbehandlung bei ungültiger Eingabe
        cerr << "Error: " << e.what() << endl;
    }

    return 0;

}

*/

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
    cout << "Helloworld2" << endl;

    printExchangeableClasses(E);
    printVectorOfSets(Ms);
    
    return 0;
}