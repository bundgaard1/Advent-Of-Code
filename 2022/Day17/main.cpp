// Advent of code 2022 - day
// Mathias Jørgensen
#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> tokenize(string l, char tokenizer) {
    vector<string> tokens;
    stringstream check(l);
    string part;
    while (getline(check, part, tokenizer)) {
        tokens.push_back(part);
    }
    return tokens;
}

int main(void) {
    ifstream inputFile;
    inputFile.open("input.txt");
    string line;

    vector<char> jets;

    getline(inputFile, line);
    for (int i = 0; i < line.size(); i++) {
        jets.push_back(line.at(i));
    }

    inputFile.close();

    return 0;
}
