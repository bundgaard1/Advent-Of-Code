#pragma once
#include "../Day.h"
#include "../utils.h"

class Day_18 : public Day {
   public:
    Day_18() = default;

    Day_18(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_18/example.txt");
                break;

            case runType::input:
                inputFile.open("day_18/input.txt");
                break;
        }
    };

    int part1solution() override {
        string line;

        int list_dx[] = {1, 0, -1, 0};
        int list_dy[] = {0, 1, 0, -1};
        vector<int> xs;
        vector<int> ys;

        int x = 0;
        int y = 0;
        int64_t trench_len = 0;

        while (getline(inputFile, line)) {
            auto tokens = tokenize(line, ' ');

            string dir = tokens[0];
            int d_index = dir == "R" ? 0 : dir == "D" ? 1 : dir == "L" ? 2 : dir == "U" ? 3 : 0;
            int dx = list_dx[d_index];
            int dy = list_dy[d_index];

            int n = stoi(tokens[1]);
            trench_len += n;

            for (int i = 0; i < n; i++) {
                xs.push_back(x);
                ys.push_back(y);
                x += dx;
                y += dy;
            }
        }

        xs.push_back(x);
        ys.push_back(y);

        int64_t A = 0;

        for (int i = 0; i < xs.size() - 1; i++) {
            A += (ys[i] + ys[i + 1]) * (xs[i] - xs[i + 1]) / 2;
        }

        // cout  << (A) << endl;

        int min_x = xs[0];
        int min_y = ys[0];
        int max_x = xs[0];
        int max_y = ys[0];

        for (int i = 0; i < xs.size(); i++) {
            // // cout  << xs[i] << ", " << ys[i] << endl;
            min_x = min(min_x, xs[i]);
            max_x = max(max_x, xs[i]);
            min_y = min(min_y, ys[i]);
            max_y = max(max_y, ys[i]);
        }
        // // cout  << min_x << endl;
        // // cout  << max_x << endl;
        // // cout  << min_y << endl;
        // // cout  << max_y << endl;

        vector<vector<bool>> grid(max_y - min_y + 1, vector<bool>(max_x - min_x + 1, false));
        for (int i = 0; i < xs.size(); i++) {
            grid[ys[i] - min_y][xs[i] - min_x] = true;
        }

        // for (auto v : grid) {
        //     for (auto a : v) {
        //         char c = a ? '#' : '.';
        //         // cout  << c;
        //     }
        //     // cout  << endl;
        // }

        stack<pair<int, int>> s;

        s.push({(max_x - min_x) / 2, (max_y - min_y) / 2});

        while (!s.empty()) {
            x = s.top().first;
            y = s.top().second;
            // // cout  << x << " " << y << endl;
            s.pop();

            if (grid[y][x] == true) {
                continue;
            } else {
                grid[y][x] = true;
            }

            for (int i = 0; i < 4; i++) {
                int dx = list_dx[i];
                int dy = list_dy[i];
                int nx = x + dx;
                int ny = y + dy;
                s.push({nx, ny});
            }
        }
        // // cout  << endl;
        int count = 0;

        for (auto v : grid) {
            for (auto a : v) {
                char c = a ? '#' : '.';
                if (a) count++;
                // // cout  << c;
            }
            // // cout  << endl;
        }

        return count;
    }

    int part2solution() override {
        string line;

        int64_t list_dx[] = {1, 0, -1, 0};
        int64_t list_dy[] = {0, 1, 0, -1};
        vector<int64_t> xs;
        vector<int64_t> ys;

        int64_t x = 0;
        int64_t y = 0;
        int64_t trench_len = 0;
        while (getline(inputFile, line)) {
            auto tokens = tokenize(line, ' ');

            char dir = tokens[2][5];
            int d_index = (tokens[2][5] - '0');
            int64_t dx = list_dx[d_index];
            int64_t dy = list_dy[d_index];

            string hexnumber = tokens[2].substr(0, 5);
            int64_t n = stoll(hexnumber, 0, 16);
            // // cout  << hexnumber << ": " << n << ", " << d_index << endl;

            trench_len += n;

            xs.push_back(x);
            ys.push_back(y);
            x += dx * n;
            y += dy * n;
        }
        xs.push_back(x);
        ys.push_back(y);

        int64_t A = 0;

        // Shoelace theorem
        for (int i = 0; i < xs.size() - 1; i++) {
            A += (xs[i] - xs[i + 1]) * ys[i];
            if ((xs[i] - xs[i + 1]) <= 0) {
                A += (xs[i] - xs[i + 1]);
            }
            if ((ys[i+1] - ys[i]) > 0) {
                A -= (ys[i+1] - ys[i]);
            }
        }

        // cout  << (A+ trench_len + 1) << endl;

        return -1;
    }
};