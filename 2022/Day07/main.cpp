// Advent of code 2022 - day 7
// Mathias Jørgensen
#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "File.cpp"

using namespace std;
vector<string> tokenize(string);
void parse_input(Directory*);

int main(void) {
        Directory* root = new Directory("/");

    parse_input(root);

    root->print_directory(0);
    cout << endl;

    root->dfs_size();

    root->print_dir_sizes(0);

    int part1 = root->part1(0);

    cout << "PART 1: " << part1 << endl;

    cout << "Total space:   70000000" << endl;
    cout << "Space use:     " << root->size << endl;
    cout << "Space to free: " << root->size - 40000000 << endl;

    int dirSpace = root->part2(root->size);

    cout << "Dir to delete: " << dirSpace << endl;

    delete (root);

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

void parse_input(Directory* root) {
    ifstream inputFile;
    inputFile.open("input.txt");
    string line;

    Directory* currentDir = root;

    // Parse the input

    while (getline(inputFile, line)) {
        // tokenize string
        vector<string> tokens = tokenize(line);

        if (tokens.at(0) == "$") {
            if (tokens.at(1) == "cd") {
                if (tokens.at(2) == "..") {
                    currentDir = currentDir->parentDirectory;
                } else {
                    for (int i = 0; i < currentDir->childDirectories.size();
                         i++) {
                        if (currentDir->childDirectories.at(i)->name ==
                            tokens.at(2)) {
                            currentDir = currentDir->childDirectories.at(i);
                        }
                    }
                }
                // cout << "change directory";
            } else {
                // cout << "list";
            }
        } else if (tokens.at(0) == "dir") {
            Directory* newDir = new Directory(tokens.at(1), currentDir);
            currentDir->push_directory(newDir);
            // cout << "Directory";
        } else {
            int size = stoi(tokens.at(0));
            File* newF = new File(tokens.at(1), size);
            currentDir->push_file(newF);
            // cout << "file";
        }
        // cout << endl;
    }
    inputFile.close();
}