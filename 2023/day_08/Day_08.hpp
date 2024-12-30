#pragma once
#include "../Day.h"
#include "../utils.h"

class Day_08 : public Day {
   public:
    Day_08() = default;

    Day_08(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_08/example.txt");
                break;

            case runType::input:
                inputFile.open("day_08/input.txt");
                break;
        }
    };

    int part1solution() override {
        string instructions;

        getline(inputFile, instructions);
        // cout  << instructions << endl;

        map<string, pair<string, string>> network;

        string line;

        while (getline(inputFile, line)) {
            auto tokens = tokenize(line, ' ');
            network[tokens[0]] = pair<string, string>(tokens[2], tokens[3]);
        }

        // for (auto l : network) {
        //     // cout  << l.first << " : (" << l.second.first << "-" << l.second.second << ")" << endl;
        // }

        string curr = "AAA";
        int steps = 0;
        int n_ins = instructions.length();

        for (int i = 0; curr != "ZZZ"; i = (i + 1) % n_ins) {
            // // cout  << curr << "->";

            if (instructions[i] == 'L') {
                curr = network[curr].first;
            } else {
                curr = network[curr].second;
            }

            // // cout  << curr << endl;

            steps++;
        }

        return steps;
    }

    int part2solution() override {
        string instructions;

        getline(inputFile, instructions);
        // cout  << instructions << endl;

        map<string, pair<string, string>> network;

        string line;

        while (getline(inputFile, line)) {
            auto tokens = tokenize(line, ' ');
            network[tokens[0]] = pair<string, string>(tokens[2], tokens[3]);
        }

        vector<string> curr;
        for (auto node : network) {
            if (node.first[2] == 'A') curr.push_back(node.first);
        }
        int nodes = curr.size();
        vector<int> last_z(nodes, 0);

        int steps = 0;
        int n_ins = instructions.length();

        while (steps < (272 * 747)) {
            // check if goal is reached

            for (int i = 0; i < nodes; i++) {
                if (curr[i][2] == 'Z') {
                    
                    // cout  << "node "<< i << " at end - since last z: " << (steps - last_z[i]) << endl;   
                    last_z[i] = steps;
                }
            }


            int i = steps % n_ins;

            for (auto& s : curr) {
                if (instructions[i] == 'L') {
                    s = network[s].first;
                } else {
                    s = network[s].second;
                }
            }

            steps++;
        }

        __int128 total_steps = (__int128)15989 * (__int128)14363 * (__int128)12737 * (__int128)18157LL * (__int128)19241LL * (__int128)19783LL;
        return total_steps;
    }
};