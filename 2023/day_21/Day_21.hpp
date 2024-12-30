#pragma once
#include "../Day.h"
#include "../utils.h"

class Day_21 : public Day {
   public:
    Day_21() = default;

    Day_21(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_21/example.txt");
                break;

            case runType::input:
                inputFile.open("day_21/input.txt");
                break;
        }
    };

    int grid_width;
    int grid_height;

    bool is_valid(int x, int y) { return x >= 0 && y >= 0 && x < grid_width && y < grid_height; }

    int part1solution() override {
        string line;
        vector<vector<char>> grid;
        int s_x;
        int s_y;

        while (getline(inputFile, line)) {
            grid.push_back(vector<char>());
            for (char c : line) {
                grid.back().push_back(c);
                if (c == 'S') {
                    s_x = grid.back().size() - 1;
                    s_y = grid.size() - 1;
                }
            }
        }

        grid_height = grid.size();
        grid_width = grid[0].size();

        set<pair<int, int>> reach;

        reach.insert({s_x, s_y});

        int64_t list_dx[] = {1, 0, -1, 0};
        int64_t list_dy[] = {0, 1, 0, -1};

        for (int i = 1; i <= 64; i++) {
            set<pair<int, int>> next_reach;

            for (auto p : reach) {
                for (int j = 0; j < 4; j++) {
                    int nx = p.first + list_dx[j];
                    int ny = p.second + list_dy[j];
                    if (grid[ny][nx] != '#' && is_valid(nx, ny)) {
                        next_reach.insert({nx, ny});
                    }
                }
            }
            // cout  << i << ": " << next_reach.size() << endl;

            reach.clear();
            reach = next_reach;
        }

        return reach.size();
    }

    int part2solution() override {
        string line;
        vector<vector<char>> grid;
    
        int s_x;
        int s_y;

        while (getline(inputFile, line)) {
            grid.push_back(vector<char>());
            for (char c : line) {
                grid.back().push_back(c);
                if (c == 'S') {
                    s_x = grid.back().size() - 1;
                    s_y = grid.size() - 1;
                }
            }
        }

        grid_height = grid.size();
        grid_width = grid[0].size();

        set<pair<int, int>> reach;

        reach.insert({s_x, s_y});

        int64_t list_dx[] = {1, 0, -1, 0};
        int64_t list_dy[] = {0, 1, 0, -1};

        for (int i = 1; i <= 64; i++) {
            set<pair<int, int>> next_reach;

            for (auto p : reach) {
                for (int j = 0; j < 4; j++) {
                    int nx = p.first + list_dx[j];
                    int ny = p.second + list_dy[j];
                    if (grid[ny][nx] != '#' && is_valid(nx, ny)) {
                        next_reach.insert({nx, ny});
                    }
                }
            }
            // // cout  << i << ": " << next_reach.size() << endl;

            reach.clear();
            reach = next_reach;
        }
        // cout  << -5 % 4 << endl;


        return reach.size();
    }
};