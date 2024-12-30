// Advent of code 2022 - day 1
// Mathias Jørgensen
#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
vector<string> tokenize(string);

struct Pos {
    int x, y;
    int px, py;

    void move(string dir) {
        this->px = x;
        this->py = y;
        switch (dir[0]) {
            case ('R'):
                this->x++;
                break;

            case ('U'):
                this->y--;
                break;

            case ('L'):
                this->x--;
                break;

            case ('D'):
                this->y++;
                break;
            default:
                break;
        }
    }

    void follow(Pos a) {
        int dist = abs(a.x - this->x) * abs(a.x - this->x) +
                   abs(a.y - this->y) * abs(a.y - this->y);
        cout << " dist: " << dist;
        int signX;
        int signY;

        if (dist >= 4) {
            if (this->x == a.x)
                signX = 0;
            else
                signX = (a.x - this->x) / abs(a.x - this->x);

            if (this->y == a.y)
                signY = 0;
            else
                signY = (a.y - this->y) / abs(a.y - this->y);

            cout << " move: " << signX << ", " << signY;
            this->x += signX;
            this->y += signY;
        }

        cout << "  {" << this->x << ", " << this->y << "}" << endl;
    }
};

int main(void) {
    ifstream inputFile;
    inputFile.open("input.txt");
    string line;

    Pos rope[10] = {{0, 0}};

    vector<Pos> visited = {rope[9]};

    // Simulate rope
    while (getline(inputFile, line)) {
        vector<string> tokens = tokenize(line);
        for (int i = 0; i < stoi(tokens.at(1)); i++) {
            rope[0].move(tokens.at(0));
            cout << "mover: 0 HEAD ";
            cout << "        {" << rope[0].x << ", " << rope[0].y << "}"
                 << endl;
            for (int j = 1; j < 10; j++) {
                cout << "mover: " << j;
                rope[j].follow(rope[j - 1]);
            }
            visited.push_back(rope[9]);
            cout << endl;
        }
    }
    // Check dublicates & delete
    for (int i = 0; i < visited.size(); i++) {
        Pos curr = visited.at(i);
        for (int j = i + 1; j < visited.size(); j++) {
            Pos comp = visited.at(j);
            if (curr.x == comp.x && curr.y == comp.y) {
                visited.erase(visited.begin() + j);
                j--;
            }
        }
    }

    // Print visited
    for (int i = 0; i < visited.size(); i++) {
        Pos curr = visited.at(i);
        cout << "{" << curr.x << ", " << curr.y << "}, ";
    }

    cout << endl << "Total visited: " << visited.size() << endl;

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