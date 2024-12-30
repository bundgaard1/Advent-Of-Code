// Advent of code 2022 - day 2
// Mathias Jørgensen
#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
#include <vector>

#define WIDTH 400
#define HEIGHT 170
#define x(a) a - 500 + WIDTH / 2

using namespace std;

struct point {
    int x, y;
};

vector<string> tokenize(string l) {
    vector<string> tokens;

    stringstream check(l);

    string part;

    // Tokenizing w.r.t. space ' '
    while (getline(check, part, ',')) {
        tokens.push_back(part);
    }

    return tokens;
}

void print_points(vector<point> points) {
    for (int i = 0; i < points.size(); i++) {
        cout << "{" << points[i].x << "," << points[i].y << "} ";
    }
    cout << endl;
}

void print_cave(char c[WIDTH][HEIGHT]) {
    cout << "---------------------------------------------------" << endl;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            cout << c[j][i];
        }
        cout << endl;
    }
}

static char cave[WIDTH][HEIGHT];

bool simulate(point s) {
    while (true) {
        if (s.y > HEIGHT) return false;

        if (cave[x(s.x)][s.y + 1] == '.') {
            s.y++;
        } else if (cave[x(s.x - 1)][s.y + 1] == '.') {
            s.x--;
            s.y++;
        } else if (cave[x(s.x + 1)][s.y + 1] == '.') {
            s.x++;
            s.y++;
        } else {
            cave[x(s.x)][s.y] = 'o';
            // cout << "landed: " << s.x << ", " << s.y << endl;
            if (s.x == 500 && s.y == 0) {
                return false;
            }

            return true;
        }
    }
}

void make_rock(point p1, point p2) {
    if (p1.x == p2.x) {
        if (p1.y < p2.y) {
            for (int i = p1.y; i <= p2.y; i++) {
                cave[x(p1.x)][i] = '#';
            }
        } else {
            for (int i = p2.y; i <= p1.y; i++) {
                cave[x(p1.x)][i] = '#';
            }
        }
    } else {
        if (p1.x < p2.x) {
            for (int i = p1.x; i <= p2.x; i++) {
                cave[x(i)][p1.y] = '#';
            }
        } else {
            for (int i = p2.x; i <= p1.x; i++) {
                cave[x(i)][p2.y] = '#';
            }
        }
    }
}

int main(void) {
    ifstream inputFile;
    inputFile.open("input.txt");

    string line;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            cave[j][i] = '.';
        }
    }
    cave[x(500)][0] = '+';

    while (getline(inputFile, line)) {
        vector<string> tokens = tokenize(line);
        vector<point> points;
        for (int i = 0; i < tokens.size(); i += 2) {
            point p;
            p.x = stoi(tokens[i]);
            p.y = stoi(tokens[i + 1]);
            points.push_back(p);
        }
        for (int i = 0; i < points.size() - 1; i++) {
            make_rock(points[i], points[i + 1]);
        }
    }

    // make floor
    for (int i = 0; i < WIDTH; i++) {
        cave[i][HEIGHT - 1] = '#';
    }

    print_cave(cave);
    int totalsand = 0;
    while (true) {
        point sand = {500, 0};
        bool landed = simulate(sand);
        if (landed) {
            // print_cave(cave);
            totalsand++;
            continue;
        } else {
            totalsand++;
            print_cave(cave);
            break;
        }
    }

    cout << "Units landed: " << totalsand << endl;

    inputFile.close();
    return 0;
}
