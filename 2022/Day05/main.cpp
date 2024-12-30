// Advent of code 2022 - day 5
// Mathias Jørgensen

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void print_stacks();
void move1(int crates, int from, int to);
void move2(int crates, int from, int to);
void input_stacks();

void part1();
void part2();

static vector<vector<char>> stacks;

int main(void) {
    input_stacks();
    // print_stacks();

    part1();
    // print_stacks();

    stacks.clear();

    input_stacks();

    part2();
    // print_stacks();

    return 0;
}

void print_stacks() {
    cout << endl;
    for (int i = 0; i < stacks.size(); i++) {
        cout << i << ' ';
        for (int j = 0; j < stacks[i].size(); j++) {
            cout << "[" << stacks[i][j] << "] ";
        }
        cout << endl;
    }
    return;
}

void part2() {
    string line;
    ifstream inputMoves;
    inputMoves.open("input_moves.txt");
    while (getline(inputMoves, line)) {
        int indexFirstSpace = line.find(' ', 0);

        int crates = stoi(line.substr(0, indexFirstSpace));
        int from = atoi(&line[indexFirstSpace + 1]);
        int to = atoi(&line[indexFirstSpace + 3]);
        // cout << crates << ' ' << from << ' ' << to << endl;
        move2(crates, from, to);
    }

    cout << "Part 2: ";
    for (int i = 1; i < 10; i++) {
        cout << stacks[i].back();
    }
    cout << endl;
    return;
}

void part1() {
    string line;
    ifstream inputMoves;
    inputMoves.open("input_moves.txt");
    while (getline(inputMoves, line)) {
        int indexFirstSpace = line.find(' ', 0);

        int crates = stoi(line.substr(0, indexFirstSpace));
        int from = atoi(&line[indexFirstSpace + 1]);
        int to = atoi(&line[indexFirstSpace + 3]);
        // cout << crates << ' ' << from << ' ' << to << endl;
        move1(crates, from, to);
    }

    cout << "Part 1: ";
    for (int i = 1; i < 10; i++) {
        cout << stacks[i].back();
    }
    cout << endl;
    return;
}

void move1(int crates, int from, int to) {
    for (int i = 0; i < crates; i++) {
        char movingCrate = stacks[from].back();
        // cout << movingCrate;
        stacks[from].pop_back();
        stacks[to].push_back(movingCrate);
    }
    return;
}

void move2(int crates, int from, int to) {
    vector<char> movingCrates;
    for (int i = 0; i < crates; i++) {
        movingCrates.push_back(stacks[from].back());
        stacks[from].pop_back();
    }
    for (int i = 0; i < crates; i++) {
        stacks[to].push_back(movingCrates.back());
        movingCrates.pop_back();
    }

    return;
}

void input_stacks() {
    string line;

    // Read stack configoration - into stacks-vector
    ifstream inputStacks;
    inputStacks.open("input_crates.txt");

    stacks.push_back({});
    while (getline(inputStacks, line)) {
        int stackNum = atoi(&line[0]);
        stacks.push_back({});
        for (int i = 2; line[i] != 0; i++) {
            if (line[i] != ' ') {
                stacks[stackNum].push_back(line[i]);
            }
        }
    }
    inputStacks.close();

    return;
}