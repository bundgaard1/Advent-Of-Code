// Advent of code 2022 - day 1
// Mathias Jørgensen
#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

vector<string> tokenize(string);

int main(void) {
    ifstream inputFile;
    inputFile.open("input.txt");

    string line;

    vector<int> cycles;

    int X = 1;
    cycles.push_back(X);

    while (getline(inputFile, line)) {
        vector<string> tokens = tokenize(line);

        if (tokens[0] == "noop") {
            cycles.push_back(X);
        }
        if (tokens[0] == "addx") {
            cycles.push_back(X);
            cycles.push_back(X);
            X += stoi(tokens[1]);
        }
    }

    int sum = 0;
    for (int i = 20; i < 221; i += 40) {
        sum += i * cycles.at(i);
        cout << "During cycle: " << i << ": " << cycles.at(i) << endl;
    }

    cout << "Sum of signal strength: " << sum << endl;

    int cursorPosition = 0;
    for (int i = 1; i < cycles.size(); i++) {
        cursorPosition++;

        int diff = abs(cycles.at(i) - cursorPosition + 1);
        if (diff < 2)
            cout << '#';
        else
            cout << '.';

        if (i % 40 == 0) {
            cursorPosition = 0;
            cout << endl;
        }
    }

    inputFile.close();
    return 0;
}

vector<string> tokenize(string l) {
    vector<string> tokens;

    stringstream check(l);

    string part;

    // Tokenizing w.r.t. space ' '
    while (getline(check, part, ' ')) {
        tokens.push_back(part);
    }

    return tokens;
}