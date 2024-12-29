#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <stdexcept> // Errorhandling


using namespace std;

// Function for determining the classes of index pairs (i,j). 
vector<set<pair<int,int>>> find_classes(vector<vector<double>> K){
    // Überprüfung auf quadratische Matrix
    size_t numRows = K.size();
    for (const auto& row : K) {
        if (row.size() != numRows) {
            throw invalid_argument("The matrix must be square.");
        }
    }
    // Check if the matrix is square
    /*
    size_t numRows = K.size();
    for (const auto& row : K) {
        if (row.size() != numRows) {
            throw invalid_argument("The matrix must be square.");
        }
    }
    */

    // Collect all index pairs, for which the entries are greater zero
    set<pair<int,int>> remaining_pairs;
    for(int i = 0; i < K.size(); i++){
        for(int j = 0; j < K.size(); j++){
            if(K[i][j] > 0){
                remaining_pairs.insert({i,j});
            }
        }
    }

    // Initialize the set of classes
    vector<set<pair<int,int>>> M_list;

    // Go through the steps 1-5 until there is no unassigned index pair anymore
    while(!remaining_pairs.empty()){

        // Initialize the class of index pairs
        set<pair<int,int>> M;

        // Choose an arbitrary unassigned index pair
        auto it = remaining_pairs.begin();
        pair<int,int> i0j0 = *it;
        remaining_pairs.erase(it);

        M.insert(i0j0);
        
        // List of new pairs to be added
        set<pair<int,int>> new_pairs;
        new_pairs.insert(i0j0);

        while(!new_pairs.empty()){
            set<pair<int,int>> current_pairs = new_pairs;
            new_pairs.clear(); // Necessary for termination condition
            
            
            // Add all the index pairs (i,j0), (i0,j) for which K(i,j0), K(i0,j) > 0
            for(const auto& p : current_pairs){
                int i = p.first;
                int j = p.second;


                for(int k = 0; k < K.size(); k++){
                    pair<int,int> temp_col = make_pair(k,j);
                    pair<int,int> temp_row = make_pair(i,k);

                    // Check through column j; the second condition assures that (k,j) is not in M yet
                    if(K[k][j] > 0 && (M.find(temp_col) == M.end())){
                        M.insert(temp_col);
                        new_pairs.insert(temp_col);
                    }
                    // Check through row i
                    if(K[i][k] > 0 && (M.find(temp_row) == M.end())){
                        M.insert(temp_row);
                        new_pairs.insert(temp_row);
                    }
                }
            }

            // Remove all pairs from remaining_pairs, that are already contained in M. 
            for(auto it = remaining_pairs.begin(); it != remaining_pairs.end(); ){
                if(M.find(*it) != M.end()){
                    it = remaining_pairs.erase(it);
                } else {
                    ++it;
                }
            }
        }

        // Add M to the family of all classes 
        M_list.push_back(M);
    }
    return M_list;
};

std::vector<std::set<int>> exchangeableClasses(const vector<vector<double>> K) {
    
    vector<set<pair<int,int>>> M = find_classes(K);
    vector<set<int>> B(M.size()); // Erstelle einen vector<set<int>> mit derselben Größe wie M
    
    for (size_t i = 0; i < M.size(); ++i) {
        for (const auto& p : M[i]) {
            B[i].insert(p.second); // Speichere die zweite Komponente jedes Paares in B
        }
    }
    
    return B;
}


// Function to output vector<set<pair<int, int>>> to the console
void printVectorOfSets(const vector<set<pair<int, int>>>& vecOfSets) {
    for (size_t i = 0; i < vecOfSets.size(); ++i) {
        cout << "Set " << i+1 << ": { ";
        for (const auto& p : vecOfSets[i]) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << "}" << endl;
    }
}



// Function to output the exchangeable classes to the console
void printExchangeableClasses(const vector<set<int>>& B) {
    for (size_t i = 0; i < B.size(); ++i) {
        cout << "Exchangeable class " << i << ": {";
        for (auto it = B[i].begin(); it != B[i].end(); ++it) {
            cout << *it;
            if (next(it) != B[i].end()) {
                cout << ", ";  // Komma nur, wenn es nicht das letzte Element ist
            }
        }
        cout << "}" << endl;
    }
}