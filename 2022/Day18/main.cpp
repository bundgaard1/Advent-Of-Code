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

    // Tokenizing w.r.t. space ' '
    while (getline(check, part, tokenizer)) {
        tokens.push_back(part);
    }

    return tokens;
}

static int totalSides = 0;
static vector<int> x;
static vector<int> y;
static vector<int> z;

static bool drop[20][20][20];
static bool exAir[20][20][20];

void total_surface() {
    for (int i = 0; i < x.size(); i++) {
        // x+
        for (int j = 0; j < x.size(); j++) {
            if (j == i) continue;
            if (y.at(i) == y.at(j) && z.at(i) == z.at(j) &&
                x.at(i) + 1 == x.at(j)) {
                totalSides--;
            }
        }
        // x-
        for (int j = 0; j < x.size(); j++) {
            if (j == i) continue;
            if (y.at(i) == y.at(j) && z.at(i) == z.at(j) &&
                x.at(i) - 1 == x.at(j)) {
                totalSides--;
            }
        }
        // y+
        for (int j = 0; j < x.size(); j++) {
            if (j == i) continue;
            if (x.at(i) == x.at(j) && z.at(i) == z.at(j) &&
                y.at(i) + 1 == y.at(j)) {
                totalSides--;
            }
        }
        // y-
        for (int j = 0; j < x.size(); j++) {
            if (j == i) continue;
            if (x.at(i) == x.at(j) && z.at(i) == z.at(j) &&
                y.at(i) - 1 == y.at(j)) {
                totalSides--;
            }
        }
        // z+
        for (int j = 0; j < x.size(); j++) {
            if (j == i) continue;
            if (y.at(i) == y.at(j) && x.at(i) == x.at(j) &&
                z.at(i) + 1 == z.at(j)) {
                totalSides--;
            }
        }
        // z-
        for (int j = 0; j < x.size(); j++) {
            if (j == i) continue;
            if (y.at(i) == y.at(j) && x.at(i) == x.at(j) &&
                z.at(i) - 1 == z.at(j)) {
                totalSides--;
            }
        }
    }
}

void exterior_air(int a, int b, int c) {
    exAir[a][b][c] = true;
    // x+
    if (a + 1 < 20 && !drop[a + 1][b][c] && !exAir[a + 1][b][c])
        exterior_air(a + 1, b, c);
    // x-
    if (a - 1 >= 0 && !drop[a - 1][b][c] && !exAir[a - 1][b][c])
        exterior_air(a - 1, b, c);
    // y+
    if (b + 1 < 20 && !drop[a][b + 1][c] && !exAir[a][b + 1][c])
        exterior_air(a, b + 1, c);
    // y-
    if (b - 1 >= 0 && !drop[a][b - 1][c] && !exAir[a][b - 1][c])
        exterior_air(a, b - 1, c);
    // z+
    if (c + 1 < 20 && !drop[a][b][c + 1] && !exAir[a][b][c + 1])
        exterior_air(a, b, c + 1);
    // z-
    if (c - 1 >= 0 && !drop[a][b][c - 1] && !exAir[a][b][c - 1])
        exterior_air(a, b, c - 1);
}

int exterior_surface() {
    int total = 0;
    for (int i = 0; i < x.size(); i++) {
        // x+
        if (exAir[x.at(i) + 1][y.at(i)][z.at(i)] || x.at(i) + 1 > 19) {
            total++;
        }
        // x-
        if (exAir[x.at(i) - 1][y.at(i)][z.at(i)] || x.at(i) - 1 < 0) {
            total++;
        }
        // y+
        if (exAir[x.at(i)][y.at(i) + 1][z.at(i)] || y.at(i) + 1 > 19) {
            total++;
        }
        // y-
        if (exAir[x.at(i)][y.at(i) - 1][z.at(i)] || y.at(i) - 1 < 0) {
            total++;
        }
        // z+
        if (exAir[x.at(i)][y.at(i)][z.at(i) + 1] || z.at(i) + 1 > 19) {
            total++;
        }
        // z-
        if (exAir[x.at(i)][y.at(i)][z.at(i) - 1] || z.at(i) - 1 < 0) {
            total++;
        }
    }
    return total;
}

void print_layer(int layer) {
    cout << "-------- Layer: " << layer << " --------" << endl;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (drop[i][j][layer]) {
                cout << '#';
            }
            if (exAir[i][j][layer]) {
                cout << '.';
            }
            if (!exAir[i][j][layer] && !drop[i][j][layer]) {
                cout << '-';
            }
        }
        cout << endl;
    }
}

int main(void) {
    ifstream inputFile;
    inputFile.open("input.txt");
    string line;

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            for (int k = 0; k < 20; k++) {
                drop[i][j][k] = false;
                exAir[i][j][k] = false;
            }
        }
    }

    while (getline(inputFile, line)) {
        vector<string> coords = tokenize(line, ',');
        x.push_back(stoi(coords.at(0)));
        y.push_back(stoi(coords.at(1)));
        z.push_back(stoi(coords.at(2)));
        totalSides += 6;
        drop[x.back()][y.back()][z.back()] = true;
    }
    inputFile.close();

    // total_surface();

    cout << "Total surface: " << totalSides << endl;

    exterior_air(0, 0, 0);

    cout << "Exterior surface area: " << exterior_surface() << endl;

    for (int i = 0; i < 20; i++) {
        print_layer(i);
    }

    return 0;
}
