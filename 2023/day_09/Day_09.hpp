#pragma once
#include "../Day.h"
#include "../utils.h"

class Day_09 : public Day {
   public:
    Day_09() = default;

    Day_09(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_09/example.txt");
                break;

            case runType::input:
                inputFile.open("day_09/input.txt");
                break;
        }
    };

    int part1solution() override {
        string line;

        vector<vector<int>> history;

        while (getline(inputFile, line)) {
            history.push_back({});
            auto tokens = tokenize(line, ' ');
            for (auto data : tokens) {
                history.back().push_back(stoi(data));
            }
        }

        int sum = 0;

        for (auto v : history) {
            print_vector(v, 1);
            vector<vector<int>> seq;

            seq.push_back(v);

            int prev_level = 0;
            while (true) {
                int iterations = seq.back().size();

                seq.push_back({});
                for (int i = 0; i < iterations - 1; i++) {
                    seq.back().push_back(seq[prev_level][i + 1] - seq[prev_level][i]);
                }
                // print_vector(seq.back(), 1);

                bool zeros = std::all_of(seq.back().begin(), seq.back().end(), [](int i) { return i == 0; });

                if (zeros) break;

                prev_level++;
            }

            int increment = 0;
            int last = 0;

            for (int i = prev_level; i >= 0; i--) {
                last = seq[i].back();
                increment = last + increment;
            }
            //// cout  << increment << " ";
            sum += increment;

            //// cout  << endl;
        }

        return sum;
    }

    int part2solution() override {
        string line;

        vector<vector<int>> history;

        while (getline(inputFile, line)) {
            history.push_back({});
            auto tokens = tokenize(line, ' ');
            for (auto data : tokens) {
                history.back().push_back(stoi(data));
            }
        }

        int sum = 0;

        for (auto v : history) {
            print_vector(v, 1);
            vector<vector<int>> seq;

            seq.push_back(v);

            int prev_level = 0;
            while (true) {
                int iterations = seq.back().size();

                seq.push_back({});
                for (int i = 0; i < iterations - 1; i++) {
                    seq.back().push_back(seq[prev_level][i + 1] - seq[prev_level][i]);
                }
                print_vector(seq.back(), 1);

                bool zeros = std::all_of(seq.back().begin(), seq.back().end(), [](int i) { return i == 0; });

                if (zeros) break;

                prev_level++;
            }

            int increment = 0;
            int last = 0;

            for (int i = prev_level; i >= 0; i--) {
                last = seq[i].front();
                increment = last - increment;
                // cout  << increment << " ";
            }
            sum += increment;

            // cout  << endl;
        }

        return sum;
    }
};