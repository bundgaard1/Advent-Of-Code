#pragma once
#include "../Day.h"
#include "../utils.h"

class Day_15 : public Day {
   public:
    Day_15() = default;

    Day_15(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_15/example.txt");
                break;

            case runType::input:
                inputFile.open("day_15/input.txt");
                break;
        }
    };

    int HASH(string& s) {
        int value = 0;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            value += c;
            value *= 17;
            value = value % 256;
        }

        return value;
    }

    int part1solution() override {
        string line;
        int sum = 0;
        while (getline(inputFile, line, ',')) {
            sum += HASH(line);
        }

        return sum;
    }

    int part2solution() override {
        string line;

        vector<vector<pair<string, int>>> boxes(256);

        while (getline(inputFile, line, ',')) {
            size_t label_end = line.find_first_of("=-");
            char operation = line[label_end];
            string label = line.substr(0, label_end);
            int hash = HASH(label);
            if (operation == '-') {
                for (int i = 0; i < boxes[hash].size();) {
                    if (boxes[hash][i].first == label) {
                        boxes[hash].erase(boxes[hash].begin() + i);
                        break;
                    } else {
                        i++;
                    }
                }
            } else {
                bool exists = false;
                for (int i = 0; i < boxes[hash].size(); i++) {
                    if (boxes[hash][i].first == label) {
                        boxes[hash][i].second = line[label_end + 1] - '0';
                        exists = true;
                        break;
                    }
                }
                if (!exists) {
                    boxes[hash].push_back(pair<string, int>(label, line[label_end + 1] - '0'));
                }
            }

            // // cout  << "After \"" << line << "\"" << endl;
            // for (int i = 0; i < boxes.size(); i++) {
            //     if (!boxes[i].empty()) {
            //         int slot = boxes[i].size();
            //         // cout  << "Box " << i << ": ";
            //         for (auto a : boxes[i]) {
            //             // cout  << "[" << a.first << " " << a.second << "]  ";
            //         }
            //         // cout  << endl;
            //     }
            // }
            // // cout  << endl;
        }

        int sum = 0;
        for (int i = 0; i < boxes.size(); i++) {
            if (!boxes[i].empty()) {
                int slot = 1;
                for (auto a : boxes[i]) {
                    sum += (i + 1) * slot * a.second;
                    // // cout  << (i + 1) * slot * a.second << " ";
                    slot++;
                }
            }
        }

        return sum;
    }
};