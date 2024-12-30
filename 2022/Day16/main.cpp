// Advent of code 2022 - day
// Mathias Jørgensen
#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
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
    unordered_map<string, int> valves;
    unordered_map<string, vector<string>> tunnels;

    ifstream inputFile;
    inputFile.open("input.txt");
    string line;

    // Parse input
    while (getline(inputFile, line)) {
        vector<string> tokens = tokenize(line, ' ');
        string name = tokens.at(0);
        int flow = stoi(tokens.at(1));
        valves[name] = flow;
        tunnels[name];
        for (int i = 2; i < tokens.size(); i++) {
            tunnels[name].push_back(tokens.at(i));
        }
    }

    // Optimize set
    unordered_map<string, unordered_map<string, int>> dists;

    for (auto valve : valves) {
        if ((valve.first != "AA") && (valve.second != 0)) {
            continue;
        }

        dists.at(valve.first).at(valve.first) = 0;
        dists.at(valve.first).at("AA") = 0;

        cout << "hej" << endl;
        set<string> visited = {valve.first};

        queue<pair<int, string>> q;

        q.push(pair<int, string>(0, valve.first));

        while (!q.empty()) {
            pair<int, string> curr = q.front();
            q.pop();

            for (auto neighbor : tunnels[curr.second]) {
                if (visited.count(neighbor)) {
                    continue;
                }
                visited.insert(neighbor);

                if (valves.at(neighbor)) {
                    dists.at(valve.first).at(neighbor) = curr.first + 1;
                }
                q.push({curr.first + 1, neighbor});
            }
        }

        dists.at(valve.first).erase(dists.at(valve.first).find(valve.first));
        if (valve.first == "AA") dists.at(valve.first).erase("AA");
    }

    for (auto dist : dists) {
        cout << dist.first << ": ";
        for (auto a : dist.second) {
            cout << "(" << a.first << ", " << a.second << "), ";
        }
        cout << endl;
    }

    inputFile.close();

    return 0;
}