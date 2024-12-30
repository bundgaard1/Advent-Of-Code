#pragma once
#include "../Day.h"
#include "../utils.h"

class Day_13 : public Day {
   public:
    Day_13() = default;

    Day_13(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_13/example.txt");
                break;

            case runType::input:
                inputFile.open("day_13/input.txt");
                break;
        }
    };
    vector<string> transpose(vector<string> p) {
        vector<string> a(p[0].length());

        for (int i = 0; i < p.size(); i++) {
            for (int j = 0; j < p[i].size(); j++) {
                a[j].push_back(p[i][j]);
            }
        }

        return a;
    }

    int part1solution() override {
        string line;

        vector<vector<string>> patterns;

        int index = 0;
        patterns.push_back(vector<string>());
        while (getline(inputFile, line)) {
            if (line == "") {
                patterns.push_back(vector<string>());
                index++;

            } else {
                patterns[index].push_back(line);
            }
        }

        int pat_no = 1;
        int num_cols = 0;
        int num_rows = 0;

        for (auto pattern : patterns) {
            // cout  << "Pattern: " << pat_no << endl;
            // for (auto s : pattern) {
            //     // cout  << s << endl;
            // }

            for (int row = 0; row < pattern.size() - 1; row++) {
                int above = row;
                int below = row + 1;
                bool reflection = true;

                while (above >= 0 && below < pattern.size()) {
                    if (pattern[above] != pattern[below]) {
                        reflection = false;
                        break;
                    } else {
                        above--;
                        below++;
                    }
                }
                if (reflection) {
                    // // cout  << "row: " << row << endl;
                    num_rows += row + 1;
                    break;
                }
            }

            auto pattern_transposed = transpose(pattern);

            for (int col = 0; col < pattern_transposed.size() - 1; col++) {
                int above = col;
                int below = col + 1;
                bool reflection = true;

                while (above >= 0 && below < pattern_transposed.size()) {
                    if (pattern_transposed[above] != pattern_transposed[below]) {
                        reflection = false;
                        break;
                    } else {
                        above--;
                        below++;
                    }
                }
                if (reflection) {
                    // // cout  << "col: " << col << endl;
                    num_cols += col + 1;
                    break;
                }
            }

            // cout  << endl;

            pat_no++;
        }

        int sum = num_rows * 100 + num_cols;

        return sum;
    }

    int part2solution() override {
        string line;

        vector<vector<string>> patterns;

        int index = 0;
        patterns.push_back(vector<string>());
        while (getline(inputFile, line)) {
            if (line == "") {
                patterns.push_back(vector<string>());
                index++;

            } else {
                patterns[index].push_back(line);
            }
        }

        int pat_no = 1;
        int num_cols = 0;
        int num_rows = 0;

        for (auto pattern : patterns) {
            // cout  << "Pattern: " << pat_no << endl;
            // for (auto s : pattern) {
            //     // cout  << s << endl;
            // }

            int row_length = pattern[0].length();

            for (int row = 0; row < pattern.size() - 1; row++) {
                int above = row;
                int below = row + 1;
                int mistakes = 0;

                while (above >= 0 && below < pattern.size()) {
                    for (int i = 0; i < row_length; i++) {
                        if (pattern[above][i] != pattern[below][i]) mistakes++;
                    }
                    if (mistakes > 1) break;

                    above--;
                    below++;
                }
                if (mistakes == 1) {
                    // cout  << "row: " << row << endl;
                    num_rows += row + 1;
                    break;
                }
            }

            auto pattern_transposed = transpose(pattern);

            int col_length = pattern.size();

            for (int col = 0; col < pattern_transposed.size() - 1; col++) {
                int above = col;
                int below = col + 1;
                bool reflection = true;

                int mistakes = 0;

                while (above >= 0 && below < pattern_transposed.size()) {
                    for (int i = 0; i < col_length; i++) {
                        if (pattern_transposed[above][i] != pattern_transposed[below][i]) mistakes++;
                    }
                    if (mistakes > 1) break;

                    above--;
                    below++;
                }
                if (mistakes == 1) {
                    // cout  << "row: " << col << endl;
                    num_cols += col + 1;
                    break;
                }
            }

            // cout  << endl;

            pat_no++;
        }

        int sum = num_rows * 100 + num_cols;

        return sum;
    }
};