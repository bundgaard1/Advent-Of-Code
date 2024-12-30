#pragma once
#include "../Day.h"
#include "../utils.h"

struct coord {
    int x, y;
    coord() : x(0), y(0) {}
    coord(int _x, int _y) : x(_x), y(_y) {}

    bool operator==(coord& rhs) { return rhs.x == x && rhs.y == y; }
};

static coord dirs[4] = {coord(0, -1), coord(1, 0), coord(0, 1), coord(-1, 0)};
static char slopes[4] = {'^', '>', 'v', '<'};

class Day_23 : public Day {
   public:
    Day_23() = default;

    Day_23(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_23/example.txt");
                break;

            case runType::input:
                inputFile.open("day_23/input.txt");
                break;
        }
    };

    vector<string> map;
    vector<string> logest_hike;
    int longest;

    coord end;

    int traverse(coord curr) {
        int so_far_max = 0;

        // // cout  << '(' << curr.x << ',' << curr.y << ":" << map[curr.y][curr.x] <<')' << endl;

        if (curr == end) {
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            coord dir = dirs[i];
            bool allowed = (curr.y + dir.y) >= 0 && (curr.y + dir.y < map.size()) && (curr.x + dir.x) >= 0 &&
                           (curr.x + dir.x < map[0].size());
            if (allowed) {
                char chardir = map[curr.y + dir.y][curr.x + dir.x];
                if (chardir == '.') {
                    map[curr.y + dir.y][curr.x + dir.x] = 'O';

                    so_far_max = max(so_far_max, traverse(coord(curr.x + dir.x, curr.y + dir.y)));

                    map[curr.y + dir.y][curr.x + dir.x] = '.';
                } else if (chardir == slopes[i]) {
                    so_far_max = max(so_far_max, traverse(coord(curr.x + dir.x, curr.y + dir.y)));
                } else {
                    continue;
                }
            }
        }

        return so_far_max + 1;
    }

    int part1solution() override {
        string line;

        while (getline(inputFile, line)) {
            map.push_back(line);
        }

        end = coord(map[0].length() - 2, map.size() - 1);

        int max = traverse(coord(1, 0));

        return max;
    }

    int traverse2(coord curr) {
        int so_far_max = 0;

       // // cout  << '(' << curr.x << ',' << curr.y <<')' << endl;

        if (curr == end) {
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            coord dir = dirs[i];
            bool allowed = (curr.y + dir.y) >= 0 && (curr.y + dir.y < map.size()) && (curr.x + dir.x) >= 0 &&
                           (curr.x + dir.x) < map[0].size();
            if (allowed) {
                char chardir = map[curr.y + dir.y][curr.x + dir.x];
                if (chardir != '#' && chardir != 'O') {
                    map[curr.y + dir.y][curr.x + dir.x] = 'O';

                    so_far_max = max(so_far_max, traverse2(coord(curr.x + dir.x, curr.y + dir.y)));

                    map[curr.y + dir.y][curr.x + dir.x] = '.';
                } 
            }
        }

        return so_far_max + 1;
    }

    int part2solution() override {
        // Not implemented
        return 1;

        map.clear();

        string line;

        while (getline(inputFile, line)) {
            map.push_back(line);
        }

        end = coord(map[0].length() - 2, map.size() - 1);
        longest = 0;

        int max = traverse2(coord(1, 0));

        return max;
    }
};