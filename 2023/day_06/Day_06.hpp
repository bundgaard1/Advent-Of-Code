#pragma once
#include "../Day.h"
#include "../utils.h"

typedef int64_t i64;

class Day_06 : public Day {
   public:
    Day_06() = default;

    Day_06(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_06/example.txt");
                break;

            case runType::input:
                inputFile.open("day_06/input.txt");
                break;
        }
    };

    int part1solution() override {
        string line;
        vector<int> time;
        vector<int> dist;

        getline(inputFile, line);
        auto tokens = tokenize(line, ' ');
        for (auto t : tokens) {
            time.push_back(stoi(t));
        }

        getline(inputFile, line);
        tokens = tokenize(line, ' ');
        for (auto t : tokens) {
            dist.push_back(stoi(t));
        }

        int sum = 1;

        for (int i = 0; i < time.size(); i++) {
            int start = 0;
            int end = 0;

            int min_dist = dist[i];
            int total_time = time[i];

            bool start_found = false;
            bool end_found = false;

            for (size_t j = 0; j < total_time; j++) {
                int end_dist = j * (total_time - j);

                // // cout  << j << ":" << end_dist << endl;
                if (!start_found && end_dist > min_dist) {
                    start = j;
                    start_found = true;
                }
                if (start_found && !end_found && end_dist <= min_dist) {
                    end = j;
                    end_found = true;
                }
            }

            // cout  << i << " : " << start << "--" << end << " " << end - start << endl;

            sum *= end - start;
        }

        return sum;
    }

    int part2solution() override {
        string line;

        getline(inputFile, line);
        auto tokens = tokenize(line, ' ');
        string combined = "";
        for (auto t : tokens) {
            combined += t;
        }
        i64 time = stoll(combined);
        // cout  << time << endl;

        getline(inputFile, line);
        tokens = tokenize(line, ' ');
        combined = "";
        for (auto t : tokens) {
            combined += t;
        }
        i64 dist = stoll(combined);
        // cout  << dist << endl;


        i64 start = 0;
        i64 end = 0;

        bool start_found = false;
        bool end_found = false;

        for (i64 j = 0; j < time; j++) {
            i64 end_dist = j * (time - j);

            // // cout  << j << ":" << end_dist << endl;
            if (!start_found && end_dist > dist) {
                start = j;
                start_found = true;
            }
            if (start_found && !end_found && end_dist <= dist) {
                end = j;
                end_found = true;
            }
        }

        // cout  << start << "--" << end << " " << end - start << endl;

        return end - start;
    }
};