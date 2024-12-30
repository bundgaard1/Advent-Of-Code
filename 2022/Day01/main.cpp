// Advent of code 2022 - day 1
// Mathias Jørgensen
#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
using namespace std;

#define ARRAY_SIZE 300

static int elves[ARRAY_SIZE] = {0};

int main(void) {
    ifstream inputFile;
    inputFile.open("input.txt");

    int index = 0;
    string line;
    int num;

    while (getline(inputFile, line)) {
        if (line.empty()) {
            index++;
        } else {
            num = stoi(line);
            elves[index] += num;
        }
    }

    sort(elves, elves + ARRAY_SIZE);

    int maxCalories = elves[0];
    int maxIndex = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (elves[i] > maxCalories) {
            maxCalories = elves[i];
            maxIndex = i;
        }
    }

    cout << "Max calories: " << maxCalories << endl;
    cout << "index:        " << maxIndex << endl;

    cout << "Top 3 elves:" << endl;
    cout << "1. " << elves[299] << endl;
    cout << "2. " << elves[298] << endl;
    cout << "3. " << elves[297] << endl;
    cout << "Total: " << elves[299] + elves[298] + elves[297] << endl;

    inputFile.close();
    return 0;
}
