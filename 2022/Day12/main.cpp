// Advent of code 2022 - day 1
// Mathias Jørgensen
#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class point {
   public:
    int x, y;
    char height;
    int distance;
    bool visited;
    point(int i_x, int i_y, char i_height) {
        x = i_x;
        y = i_y;
        height = i_height;
        distance = 10000;
        visited = false;
    }
};

void print_map(vector<vector<point>> map);
void check_neightbors(point* curr);
void print_unvisited();
void print_distances(vector<vector<int>> d);
void print_path(vector<point*> path);

static vector<point*> unvisited;
static vector<vector<point>> map;
static vector<vector<int>> distances;

int main(void) {
    ifstream inputFile;
    inputFile.open("input.txt");
    string line;

    extern vector<vector<point>> map;

    int y = 0;
    while (getline(inputFile, line)) {
        map.push_back({});
        distances.push_back({});
        for (int i = 0; i < line.size(); i++) {
            if (line.at(i) == 'E') line.at(i) = 'z';
            map.at(y).push_back(point(i, y, line.at(i)));
            distances.at(y).push_back(0);
        }
        y++;
    }
    point* curr;
    int shortest = 1000;

    for (int i = 0; i < map.size(); i++) {
        /* code */
        curr = &map.at(i).at(0);

        curr->distance = 0;
        curr->height = 'a';
        curr->visited = true;
        // Check neightbors
        check_neightbors(curr);
        // print_unvisited();
        int dist_to_E = 1000;

        while (!unvisited.empty()) {
            curr = unvisited.front();
            distances.at(curr->y).at(curr->x) = curr->distance;
            if (curr->height == 'z') {
                if (curr->distance < dist_to_E) {
                    dist_to_E = curr->distance;
                }
            }

            unvisited.erase(unvisited.begin());
            check_neightbors(curr);
        }
        if (dist_to_E < shortest) {
            cout << "update: " << shortest << " -> " << dist_to_E << endl;
            shortest = dist_to_E;
        }
    }

    cout << "shortest Distance to E: " << shortest;

    // print_path(best_path);
    inputFile.close();
    return 0;
}

void print_map(vector<vector<point>> map) {
    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map.at(y).size(); x++) {
            cout << map.at(y).at(x).height;
        }
        cout << endl;
    }
}

void check_neightbors(point* curr) {
    extern vector<point*> unvisited;
    extern vector<vector<point>> map;
    // left
    if (curr->x - 1 >= 0) {
        if (map.at(curr->y).at(curr->x - 1).height <= curr->height + 1) {
            point* left = &map.at(curr->y).at(curr->x - 1);
            if (!left->visited || left->distance - 1 > curr->distance) {
                unvisited.push_back(left);
                left->distance = curr->distance + 1;
                left->visited = true;
            }
        }
    }
    // UP
    if (curr->y - 1 >= 0) {
        if (map.at(curr->y - 1).at(curr->x).height <= curr->height + 1) {
            point* up = &map.at(curr->y - 1).at(curr->x);
            if (!up->visited || up->distance - 1 > curr->distance) {
                unvisited.push_back(up);
                up->distance = curr->distance + 1;
                up->visited = true;
            }
        }
    }
    // RIGHT
    if (curr->x + 1 < map.at(0).size()) {
        if (map.at(curr->y).at(curr->x + 1).height <= curr->height + 1) {
            point* right = &map.at(curr->y).at(curr->x + 1);
            if (!right->visited || right->distance - 1 > curr->distance) {
                unvisited.push_back(right);
                right->distance = curr->distance + 1;
                right->visited = true;
            }
        }
    }
    // DOWN
    if (curr->y + 1 < map.size()) {
        if (map.at(curr->y + 1).at(curr->x).height <= curr->height + 1) {
            point* down = &map.at(curr->y + 1).at(curr->x);
            if (!down->visited || down->distance - 1 > curr->distance) {
                unvisited.push_back(down);
                down->distance = curr->distance + 1;
                down->visited = true;
            }
        }
    }
}

void print_unvisited() {
    extern vector<point*> unvisited;
    cout << "Unvisited: ";
    for (int i = 0; i < unvisited.size(); i++) {
        point* curr = unvisited.at(i);
        cout << " {" << curr->x << ", " << curr->y << ", " << curr->height
             << "}, ";
    }
    cout << endl;
}

void print_distances(vector<vector<int>> d) {
    ofstream myfile;
    myfile.open("dist.txt");

    for (int y = 0; y < d.size(); y++) {
        for (int x = 0; x < d.at(y).size(); x++) {
            printf("%4d ", d.at(y).at(x));
            char buffer[10];
            sprintf(buffer, "%4d ", d.at(y).at(x));
            myfile << buffer;
        }
        myfile << endl;
        cout << endl;
    }
    myfile.close();
}

void print_path(vector<point*> path) {
    for (int i = 0; i < path.size(); i++) {
        point* curr = path.at(i);
        cout << " {" << curr->x << "," << curr->y << "," << curr->height << "}"
             << endl;
    }
    cout << "Path size: " << path.size() << endl;
}