#pragma once
#include "../Day.h"
#include "../utils.h"

class Day_10 : public Day {
   public:
    Day_10() = default;

    Day_10(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_10/example.txt");
                break;

            case runType::input:
                inputFile.open("day_10/input.txt");
                break;
        }
    };

    int tiles_x_max = 0;
    int tiles_y_max = 0;

    struct coord {
        int x;
        int y;
        int dist = 0;

        coord(int _x, int _y) : x(_x), y(_y) {}
        bool operator<(const coord& a) const { return (dist << 16 + y << 8 + x) < (a.dist << 16 + a.y << 8 + a.x); }
        bool operator==(const coord& a) const { return (dist == a.dist) && (x == a.x) && (y == a.y); }
    };

    bool is_valid(coord c) {
        bool a = (c.x >= 0 && c.y >= 0 && c.x < tiles_x_max && c.y < tiles_y_max);
        // if (a) // // cout   << "Invalid coord" << endl;
        return a;
    }

    int part1solution() override {
        string line;

        vector<string> tiles;

        while (getline(inputFile, line)) {
            tiles.push_back(line);
        }

        tiles_x_max = tiles[0].length();
        tiles_y_max = tiles.size();

        size_t s_x = -1;
        size_t s_y = -1;
        for (size_t i = 0; i < tiles.size(); i++) {
            s_x = tiles.at(i).find('S');
            if (s_x != string::npos) {
                s_y = i;
                break;
            }
        }

        // // cout   << s_x << ", " << s_y << endl;

        queue<coord> open;
        set<pair<int, int>> closed;

        closed.insert(pair<int, int>(s_x, s_y));

        auto right = coord(s_x + 1, s_y);
        if (is_valid(right)) {
            char right_c = tiles[right.y][right.x];
            if (right_c == '7' || right_c == '-' || right_c == 'J') {
                right.dist = 1;
                open.push(right);
            }
        }

        auto left = coord(s_x - 1, s_y);
        if (is_valid(left)) {
            char left_c = tiles[left.y][left.x];
            if (left_c == 'L' || left_c == '-' || left_c == 'F') {
                left.dist = 1;
                open.push(left);
            }
        }

        auto up = coord(s_x, s_y - 1);
        if (is_valid(up)) {
            char up_c = tiles[up.y][up.x];
            if (up_c == 'F' || up_c == '|' || up_c == '7') {
                up.dist = 1;
                open.push(up);
            }
        }

        auto down = coord(s_x, s_y + 1);
        if (is_valid(down)) {
            char down_c = tiles[down.y][down.x];
            if (down_c == 'J' || down_c == '|' || down_c == 'L') {
                down.dist = 1;
                open.push(down);
            }
        }

        int max_d = 0;

        while (open.size() > 0) {
            coord curr = open.front();

            char curr_c = tiles[curr.y][curr.x];

            // // // cout   << "(" << curr.x << ", " << curr.y << ") dist: " << curr.dist << "  char: " << curr_c << endl;

            if (curr_c == 'L' || curr_c == '-' || curr_c == 'F') {
                coord right = coord(curr.x + 1, curr.y);
                if (is_valid(right) && !closed.count(pair<int, int>(right.x, right.y))) {
                    right.dist = 1 + curr.dist;
                    open.push(right);
                }
            }
            if (curr_c == '7' || curr_c == '|' || curr_c == 'F') {
                coord down = coord(curr.x, curr.y + 1);
                if (is_valid(down) && !closed.count(pair<int, int>(down.x, down.y))) {
                    down.dist = 1 + curr.dist;
                    open.push(down);
                }
            }
            if (curr_c == '7' || curr_c == '-' || curr_c == 'J') {
                coord left = coord(curr.x - 1, curr.y);
                if (is_valid(left) && !closed.count(pair<int, int>(left.x, left.y))) {
                    left.dist = 1 + curr.dist;
                    open.push(left);
                }
            }
            if (curr_c == 'L' || curr_c == '|' || curr_c == 'J') {
                coord up = coord(curr.x, curr.y - 1);
                if (is_valid(up) && !closed.count(pair<int, int>(up.x, up.y))) {
                    up.dist = 1 + curr.dist;
                    open.push(up);
                }
            }

            closed.insert(pair<int, int>(curr.x, curr.y));

            max_d = max(max_d, curr.dist);

            open.pop();
        }

        return max_d;
    }

    int part2solution() override {
        string line;

        vector<string> tiles;

        while (getline(inputFile, line)) {
            tiles.push_back(line);
        }

        tiles_x_max = tiles[0].length();
        tiles_y_max = tiles.size();

        size_t s_x = -1;
        size_t s_y = -1;
        for (size_t i = 0; i < tiles.size(); i++) {
            s_x = tiles.at(i).find('S');
            if (s_x != string::npos) {
                s_y = i;
                break;
            }
        }

        // // cout   << s_x << ", " << s_y << endl;

        queue<coord> open;
        set<pair<int, int>> closed;

        closed.insert(pair<int, int>(s_x, s_y));

        auto right = coord(s_x + 1, s_y);
        if (is_valid(right)) {
            char right_c = tiles[right.y][right.x];
            if (right_c == '7' || right_c == '-' || right_c == 'J') {
                right.dist = 1;
                open.push(right);
            }
        }

        auto left = coord(s_x - 1, s_y);
        if (is_valid(left)) {
            char left_c = tiles[left.y][left.x];
            if (left_c == 'L' || left_c == '-' || left_c == 'F') {
                left.dist = 1;
                open.push(left);
            }
        }

        auto up = coord(s_x, s_y - 1);
        if (is_valid(up)) {
            char up_c = tiles[up.y][up.x];
            if (up_c == 'F' || up_c == '|' || up_c == '7') {
                up.dist = 1;
                open.push(up);
            }
        }

        auto down = coord(s_x, s_y + 1);
        if (is_valid(down)) {
            char down_c = tiles[down.y][down.x];
            if (down_c == 'J' || down_c == '|' || down_c == 'L') {
                down.dist = 1;
                open.push(down);
            }
        }

        int max_d = 0;

        while (open.size() > 0) {
            coord curr = open.front();

            char curr_c = tiles[curr.y][curr.x];

            // // // cout   << "(" << curr.x << ", " << curr.y << ") dist: " << curr.dist << "  char: " << curr_c << endl;

            if (curr_c == 'L' || curr_c == '-' || curr_c == 'F') {
                coord right = coord(curr.x + 1, curr.y);
                if (is_valid(right) && !closed.count(pair<int, int>(right.x, right.y))) {
                    right.dist = 1 + curr.dist;
                    open.push(right);
                }
            }
            if (curr_c == '7' || curr_c == '|' || curr_c == 'F') {
                coord down = coord(curr.x, curr.y + 1);
                if (is_valid(down) && !closed.count(pair<int, int>(down.x, down.y))) {
                    down.dist = 1 + curr.dist;
                    open.push(down);
                }
            }
            if (curr_c == '7' || curr_c == '-' || curr_c == 'J') {
                coord left = coord(curr.x - 1, curr.y);
                if (is_valid(left) && !closed.count(pair<int, int>(left.x, left.y))) {
                    left.dist = 1 + curr.dist;
                    open.push(left);
                }
            }
            if (curr_c == 'L' || curr_c == '|' || curr_c == 'J') {
                coord up = coord(curr.x, curr.y - 1);
                if (is_valid(up) && !closed.count(pair<int, int>(up.x, up.y))) {
                    up.dist = 1 + curr.dist;
                    open.push(up);
                }
            }

            closed.insert(pair<int, int>(curr.x, curr.y));

            max_d = max(max_d, curr.dist);

            open.pop();
        }

        int count = 0;
        set<pair<int, int>> inside_tiles;

        for (size_t y = 0; y < tiles_y_max; y++) {
            bool inside = false;
            for (size_t x = 0; x < tiles_x_max; x++) {
                if (closed.count(pair<int, int>(x, y))) {
                    char curr_c = tiles[y][x];

                    if (curr_c == '|') {
                        inside = !inside;
                    }
                    if (curr_c == 'L') {
                        while (tiles[y][++x] == '-' && x < tiles_x_max) {
                            continue;
                        }

                        char next_c = tiles[y][x];
                        // // // cout   << "(" << x << ", " << y << ") " << next_c << endl;
                        if (next_c == '7') {
                            inside = !inside;
                        } else if (next_c == 'J') {
                            continue;
                        }
                    }
                    if (curr_c == 'F') {
                        while (tiles[y][++x] == '-' && x < tiles_x_max) {
                            continue;
                        }
                        char next_c = tiles[y][x];
                        // // // cout   << "(" << x << ", " << y << ") " << next_c << endl;
                        if (next_c == '7') {
                            continue;
                        } else if (next_c == 'J' || next_c == 'S') {
                            inside = !inside;
                        }
                    }
                    continue;
                } else {
                    if (inside) {
                        count++;
                        // // // cout   << "inside:  " << "(" << x << ", " << y << ")" << endl;
                    }
                }
            }
        }

        return count;
    }
};