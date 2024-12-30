// Advent of code 2022 - day 4
// Mathias Jørgensen

#include <fstream>
#include <iostream>
using namespace std;

bool contains(string line) {
    int length = line.length();
    int commaIndex = line.find(',', 0);
    int firstIndex = line.find('-', 0);
    int secondIndex = line.find('-', firstIndex + 1);

    cout << line << endl;
    // cout << firstIndex << ' ' << commaIndex << ' ' << secondIndex << ' '<<
    // length << endl;

    string sectionsS[4] = {};
    sectionsS[0] = line.substr(0, firstIndex);
    sectionsS[1] = line.substr(firstIndex + 1, commaIndex - firstIndex - 1);
    sectionsS[2] = line.substr(commaIndex + 1, secondIndex - commaIndex - 1);
    sectionsS[3] = line.substr(secondIndex + 1, length - secondIndex - 1);

    // cout << sections[0] << ' ' << sections[1] << ' ' << sections[2] << ' '<<
    // sections[3] << endl << endl;

    int sections[4] = {0};

    for (int i = 0; i < 4; i++) {
        sections[i] = stoi(sectionsS[i]);
    }

    if (sections[0] >= sections[2] && sections[1] <= sections[3]) {
        return true;
    } else if (sections[2] >= sections[0] && sections[3] <= sections[1]) {
        return true;
    }

    return false;
}

bool overlap(string line) {
    int length = line.length();
    int commaIndex = line.find(',', 0);
    int firstIndex = line.find('-', 0);
    int secondIndex = line.find('-', firstIndex + 1);

    // cout << line << endl;

    string sectionsS[4] = {};
    sectionsS[0] = line.substr(0, firstIndex);
    sectionsS[1] = line.substr(firstIndex + 1, commaIndex - firstIndex - 1);
    sectionsS[2] = line.substr(commaIndex + 1, secondIndex - commaIndex - 1);
    sectionsS[3] = line.substr(secondIndex + 1, length - secondIndex - 1);

    int sections[4] = {0};

    for (int i = 0; i < 4; i++) {
        sections[i] = stoi(sectionsS[i]);
    }

    bool used[100] = {false};

    for (int i = sections[0]; i <= sections[1]; i++) {
        used[i] = true;
    }
    for (int i = sections[2]; i <= sections[3]; i++) {
        if (used[i]) {
            return true;
        }
    }

    return false;
}

int main(void) {
    ifstream inputFile;
    inputFile.open("input");

    string line;
    int pairsContained = 0;
    int pairsOverlap = 0;

    while (getline(inputFile, line)) {
        if (contains(line)) {
            pairsContained++;
            cout << "contains" << endl;
        }
        if (overlap(line)) {
            pairsOverlap++;
            cout << "overlap" << endl;
        }
    }

    cout << "Pairs contained: " << pairsContained << endl;
    cout << "Pairs overlap: " << pairsOverlap << endl;

    inputFile.close();
    return 0;
}
