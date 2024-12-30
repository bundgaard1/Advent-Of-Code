// Advent of code 2022 - day 1
// Mathias Jørgensen
#include <bits/stdc++.h>

#include <fstream>
#include <iostream>

#define SEQUENCE 14

using namespace std;
bool no_dublicate(string sub);

int main(void) {
    ifstream inputFile;
    inputFile.open("input.txt");
    string line;

    getline(inputFile, line);

    for (int i = 0; i < line.size() - SEQUENCE + 1; i++) {
        string sub = line.substr(i, SEQUENCE);
        if (no_dublicate(sub)) {
            cout << i + SEQUENCE << ": " << sub << endl;
            break;
        }
    }

    inputFile.close();
    return 0;
}

bool no_dublicate(string sub) {
    bool contains[26] = {false};

    for (int i = 0; i < SEQUENCE; i++) {
        int index = sub[i] - 97;
        // cout << sub[i] << index;
        if (contains[index]) {
            return false;
        }
        contains[index] = true;
    }

    return true;
}