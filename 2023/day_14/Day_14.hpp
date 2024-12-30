#pragma once
#include "../Day.h"
#include "../utils.h"

class Day_14 : public Day {
   public:
    Day_14() = default;

    Day_14(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_14/example.txt");
                break;

            case runType::input:
                inputFile.open("day_14/input.txt");
                break;
        }
    };

    int part1solution() override {
        string line;

        vector<string> map;

        while (getline(inputFile, line)) {
            map.push_back(line);
        }
        int map_height = map.size();
        int map_width = map[0].size();
        int sum = 0;

        for (int y = 0; y < map_height; y++) {
            for (int x = 0; x < map_width; x++) {
                if (map[y][x] == 'O') {
                    // rool
                    int y_above = y - 1;
                    while (y_above >= 0 && map[y_above][x] == '.') {
                        y_above--;
                    }

                    map[y][x] = '.';
                    map[y_above + 1][x] = 'O';
                    // // cout  << map.size() - y_above << endl;
                    sum += map_height - y_above - 1;
                }
            }
            // for (auto l : map) {
            //     // cout  << l << endl;
            // }
            // // cout  << endl;
        }

        return sum;
    }

    void simulate(vector<string>& map) {
        int map_height = map.size();
        int map_width = map[0].size();

        // north
        for (int y = 0; y < map_height; y++) {
            for (int x = 0; x < map_width; x++) {
                if (map[y][x] == 'O') {
                    int above = y - 1;
                    while (above >= 0 && map[above][x] == '.') above--;

                    map[y][x] = '.';
                    map[above + 1][x] = 'O';
                }
            }
        }
        // west
        for (int x = 0; x < map_width; x++) {
            for (int y = 0; y < map_height; y++) {
                if (map[y][x] == 'O') {
                    int left = x - 1;
                    while (left >= 0 && map[y][left] == '.') left--;

                    map[y][x] = '.';
                    map[y][left + 1] = 'O';
                }
            }
        }

        // south
        for (int y = map_height - 1; y >= 0; y--) {
            for (int x = 0; x < map_width; x++) {
                if (map[y][x] == 'O') {
                    int below = y + 1;
                    while (below < map_height && map[below][x] == '.') below++;

                    map[y][x] = '.';
                    map[below - 1][x] = 'O';
                }
            }
        }

        // east
        for (int x = map_width - 1; x >= 0; x--) {
            for (int y = 0; y < map_height; y++) {
                if (map[y][x] == 'O') {
                    int right = x + 1;
                    while (right >= 0 && map[y][right] == '.') right++;

                    map[y][x] = '.';
                    map[y][right - 1] = 'O';
                }
            }
        }
    }

    int total_load(const vector<string>& map) {
        int map_height = map.size();
        int map_width = map[0].size();
        int sum = 0;
        for (int y = 0; y < map_height; y++) {
            for (int x = 0; x < map_width; x++) {
                if (map[y][x] == 'O') {
                    sum += map_height - y;
                }
            }
        }
        return sum;
    }

    void print_map(const vector<string>& map, int cycle) {
        // cout  << "After " << cycle << " cycle" << endl;
        for (auto l : map) {
            // cout  << l << endl;
        }
        // cout  << endl;
    }

    int part2solution() override {
        string line;

        vector<string> rocks;

        while (getline(inputFile, line)) {
            rocks.push_back(line);
        }

        map<int, vector<int>> load_records;

        for (int i = 1; i <= 1000000000; i++) {
            if(i == 110){
                while(i + 900000000 < 1000000000){
                    i +=  900000000;
                }
                while(i + 9000 < 1000000000){
                    i += 9000;
                }
                while(i + 9 < 1000000000){
                    i += 9;
                }
            }


            simulate(rocks);
            int load = total_load(rocks);
            // // cout  << i << ": " << load << endl;

            if (load_records.find(load) != load_records.end()) {
                load_records[load].push_back(i);
            } else {
                load_records[load] = vector<int>();
                load_records[load].push_back(i);
            }
        }

        for (auto load : load_records) {
            // cout  << "Load: " << load.first << ": ";
            print_vector(load.second, 1);
        }

        return -1;
    }
};