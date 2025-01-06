#include "header.h"

// Burrows-Wheeler Transform
string burrowsWheelerTransform(string s) {
    int n = s.size();
    
    vector<string> rotations;

    // Generate all rotations of the string
    for (int i = 0; i < n; ++i) {
        rotations.push_back(s.substr(i) + s.substr(0, i));
    }

    // Sort rotations lexicographically
    sort(rotations.begin(), rotations.end());

    // Construct the BWT result
    string bwt = "";

    for (int i = 0; i < n; ++i) {
        bwt += rotations[i][n - 1]; // Last column of the sorted rotations
    }

    return bwt;
}

// Inverse Burrows-Wheeler Transform
string inverseBurrowsWheelerTransform(string bwt) {
    int n = bwt.size();

    // Initialize a table with n empty strings, this will be the original BWT Table
    vector<string> table(n, "");

    // Iteratively build the table
    for (int i = 0; i < n; ++i) {
        // Prepend BWT characters to each row
        for (int j = 0; j < n; ++j) {
            table[j] = bwt[j] + table[j];
        }

        // Sort the table after each iteration
        sort(table.begin(), table.end());
    }

    // Find the row that ends with the EOS symbol '$'
    for (int i = 0; i < n; ++i) {
        if (table[i].back() == '$') {
            return table[i];
        }
    }

    return ""; // ERROR
}

vector<int> BWTPatternMatching(string bwt, string pattern) {
    int n = bwt.size();
    int patternSize = pattern.size();

    // Build firstOccurrence[] to store first position of each symbol
    unordered_map<char, int> firstOccurrence; // 26 symbols from alphabet, 1 'space' character, 1 '$' character
    firstOccurrence['$'] = -1;
    firstOccurrence[' '] = -1;
    for (char ch = 'a'; ch <= 'z'; ch++) {
        firstOccurrence[ch] = -1;
    }

    string firstColumn = bwt;
    sort(firstColumn.begin(), firstColumn.end());

    for (int i = 0; i < firstColumn.size(); i++) {
        if (firstOccurrence[firstColumn[i]] == -1)
            firstOccurrence[firstColumn[i]] = i;
    }

    // Build count[] to store occurences of symbol in the first 'i' position of the LastColumn ('bwt' string)
    vector<unordered_map<char, int>> count(n + 1);
    count[0]['$'] = 0;
    count[0][' '] = 0;
    for (char ch = 'a'; ch <= 'z'; ch++) {
        count[0][ch] = 0;
    }

    for (int i = 1; i <= n; i++) {
        count[i] = count[i - 1];
        count[i][bwt[i - 1]]++;
    }    

    // Main process
    int top = 0;
    int bottom = n - 1;

    while (top <= bottom) {
        if (pattern != "") {
            char symbol = pattern[pattern.size() - 1];
            pattern.erase(pattern.size() - 1);

            top = firstOccurrence[symbol] + count[top][symbol];
            bottom = firstOccurrence[symbol] + count[bottom + 1][symbol] - 1;

            // cout << "top: " << top << ", " << "bottom: " << bottom << endl;
        }
        else { // End process
            // cout << "Number of occurrences: " << bottom - top + 1 << endl;
            // return bottom - top + 1;
    
            // Collect starting positions of all matches
            vector<int> positions;
            for (int i = top; i <= bottom; ++i) {
                int index = i;

                // Recover the position in the original string
                int position = 0;
                while (firstColumn[index] != '$') {
                    position++;
                    index = firstOccurrence[bwt[index]] + count[index][bwt[index]];
                }
                positions.push_back(position - 1); // Adjust position to original string
            }

            sort(positions.begin(), positions.end());
            return positions;
        }
    }
    
    return {}; // ERROR
}