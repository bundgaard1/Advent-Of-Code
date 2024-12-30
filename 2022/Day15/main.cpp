// Advent of code 2022 - day
// Mathias Jørgensen
#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct sensor {
    int x;
    int y;
    int closest_beacon;
};
struct beacon {
    int x;
    int y;
};

int man_dist(int x1, int y1, int x2, int y2) {
    int dx = abs(x1 - x2);
    int dy = abs(y1 - y2);
    return dx + dy;
}

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

int main(void) {
    ifstream inputFile;
    inputFile.open("input.txt");
    string line;
    int biggestX;
    int biggestY;

    vector<sensor> sensors;
    vector<beacon> beacons;

    while (getline(inputFile, line)) {
        vector<string> coords = tokenize(line, ' ');

        vector<string> s = tokenize(coords[0], ',');
        sensor new_s;
        new_s.x = stoi(s[0]);
        new_s.y = stoi(s[1]);

        vector<string> b = tokenize(coords[1], ',');
        beacon new_b;
        new_b.x = stoi(b[0]);
        new_b.y = stoi(b[1]);

        new_s.closest_beacon = man_dist(new_s.x, new_s.y, new_b.x, new_b.y);

        sensors.push_back(new_s);
        beacons.push_back(new_b);
    }
    inputFile.close();
    int positions = 0;

    for (int y = 0; y < 4000000; y++) {
        for (int x = 0; x < 4000000; x++) {
            bool contained = false;
            for (int j = 0; j < sensors.size(); j++) {
                sensor curr_s = sensors.at(j);
                int dist = man_dist(x, y, curr_s.x, curr_s.y);
                if (dist <= curr_s.closest_beacon) {
                    contained = true;
                    x += curr_s.closest_beacon - dist;
                }
            }
            if (contained) {
                // cout << "Not found: {" << x << ", " << y << "} " << endl;
            } else {
                cout << "FOUND: {" << x << ", " << y << "} " << endl;

                y += 4000000;
                x += 4000000;
            }
        }
    }

    // cout << "Positions cannot contain beacon: " << positions << endl;

    return 0;
}
