#pragma once
#include "../Day.h"
#include "../utils.h"

class Day_17 : public Day {
   public:
    Day_17() = default;

    Day_17(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_17/example.txt");
                break;

            case runType::input:
                inputFile.open("day_17/input.txt");
                break;
        }
    };

    int layout_height;
    int layout_width;

    enum heading {
        up,
        down,
        left,
        right,
        no,
    };

    pair<int, int> next_pos(int x, int y, heading prev) {
        if (prev == heading::down) {
            return pair<int, int>(x, y - 1);
        } else if (prev == heading::up) {
            return pair<int, int>(x, y + 1);
        } else if (prev == heading::right) {
            return pair<int, int>(x - 1, y);
        } else if (prev == heading::left) {
            return pair<int, int>(x + 1, y);
        }
        return pair<int, int>(x, y);
    }

    int get_index(int x, int y) { return y * layout_width + x; }

    bool is_valid(int x, int y) { return (0 <= x && x < layout_width) && (0 <= y && y < layout_height); }

    struct state {
        int64_t hl;
        int64_t x;
        int64_t y;
        int64_t dx;
        int64_t dy;
        int64_t n;

        state(int64_t _hl, int64_t _x, int64_t _y, int64_t _dx, int64_t _dy, int64_t _n)
            : hl(_hl), x(_x), y(_y), dx(_dx), dy(_dy), n(_n) {}

        bool operator<(const state& rhs) const { return hl > rhs.hl; }
    };

    int part1solution() override {
        string line;

        vector<vector<int>> grid;
        int list_dx[] = {0, 1, 0, -1};
        int list_dy[] = {-1, 0, 1, 0};

        while (getline(inputFile, line)) {
            grid.push_back(vector<int>());
            for (auto c : line) {
                grid.back().push_back(c - '0');
            }
        }

        layout_height = grid.size();
        layout_width = grid[0].size();

        set<int64_t> seen;
        priority_queue<state> pq;
        pq.push(state(0, 0, 0, 0, 0, 0));

        while (!pq.empty()) {
            state curr = move(pq.top());
            pq.pop();

            // // // cout   << "(" << curr.x << ", " << curr.y << "): " << curr.hl << endl;

            if (curr.x == (layout_height - 1) && curr.y == (layout_width - 1)) {
                // // cout   << curr.hl;
                break;
            }

            int64_t seen_key = (curr.x << 32) + (curr.y << 16) + (curr.dx << 8) + (curr.dy << 4) + curr.n;

            if (seen.count(seen_key)) {
                // // // cout   << "seen" << endl;
                continue;
            }

            seen.insert(seen_key);

            if (curr.n < 3 && (pair<int, int>{curr.dx, curr.dy} != pair<int, int>{0, 0})) {
                int nx = curr.x + curr.dx;
                int ny = curr.y + curr.dy;
                if (is_valid(nx, ny)) {
                    pq.push(state(curr.hl + grid[ny][nx], nx, ny, curr.dx, curr.dy, curr.n + 1));
                }
            }

            for (int i = 0; i < 4; i++) {
                int ndx = list_dx[i];
                int ndy = list_dy[i];
                if ((pair<int, int>{curr.dx, curr.dy} != pair<int, int>{ndx, ndy}) &&
                    (pair<int, int>{curr.dx, curr.dy} != pair<int, int>{-ndx, -ndy})) {
                    int nx = curr.x + ndx;
                    int ny = curr.y + ndy;
                    if (is_valid(nx, ny)) {
                        pq.push(state(curr.hl + grid[ny][nx], nx, ny, ndx, ndy, 1));
                    }
                }
            }
        }
        return 1;
    }

    int part2solution() override {
        string line;

        vector<vector<int>> grid;
        int list_dx[] = {0, 1, 0, -1};
        int list_dy[] = {-1, 0, 1, 0};

        while (getline(inputFile, line)) {
            grid.push_back(vector<int>());
            for (auto c : line) {
                grid.back().push_back(c - '0');
            }
        }

        layout_height = grid.size();
        layout_width = grid[0].size();

        set<int64_t> seen;
        priority_queue<state> pq;
        pq.push(state(0, 0, 0, 0, 0, 0));

        while (!pq.empty()) {
            state curr = move(pq.top());
            pq.pop();

            // // // cout   << "(" << curr.x << ", " << curr.y << "): " << curr.hl << endl;

            if (curr.x == (layout_height - 1) && curr.y == (layout_width - 1) && curr.n >= 4) {
                // // cout   << curr.hl << endl;
                break;
            }

            int64_t seen_key = (curr.x << 32) + (curr.y << 16) + (curr.dx << 8) + (curr.dy << 4) + curr.n;

            if (seen.count(seen_key)) {
                // // // cout   << "seen" << endl;
                continue;
            }

            seen.insert(seen_key);

            if (curr.n < 10 && (pair<int, int>{curr.dx, curr.dy} != pair<int, int>{0, 0})) {
                int nx = curr.x + curr.dx;
                int ny = curr.y + curr.dy;
                if (is_valid(nx, ny)) {
                    pq.push(state(curr.hl + grid[ny][nx], nx, ny, curr.dx, curr.dy, curr.n + 1));
                }
            }

            if (curr.n >= 4 || (pair<int, int>{curr.dx, curr.dy} == pair<int, int>{0, 0})) {
                for (int i = 0; i < 4; i++) {
                    int ndx = list_dx[i];
                    int ndy = list_dy[i];
                    if ((pair<int, int>{curr.dx, curr.dy} != pair<int, int>{ndx, ndy}) &&
                        (pair<int, int>{curr.dx, curr.dy} != pair<int, int>{-ndx, -ndy})) {
                        int nx = curr.x + ndx;
                        int ny = curr.y + ndy;
                        if (is_valid(nx, ny)) {
                            pq.push(state(curr.hl + grid[ny][nx], nx, ny, ndx, ndy, 1));
                        }
                    }
                }
            }
        }
        return 1;

        return -1;
    }
};