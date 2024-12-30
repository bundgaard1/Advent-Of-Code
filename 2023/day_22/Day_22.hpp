#pragma once
#include <vector>

#include "../Day.h"
#include "../utils.h"

using namespace std;

class Day_22 : public Day {
   public:
    Day_22() = default;

    Day_22(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_22/example.txt");
                break;

            case runType::input:
                inputFile.open("day_22/input.txt");
                break;
        }
    };

    struct coord {
        // Hexadecimal: xyzz
        int point;

        coord() : point(0) {}

        coord(int point) : point(point) {}

        coord(int x, int y, int z) { point = (x << 24) + (y << 16) + z; }

        inline int x() { return (point & 0xff000000) >> 24; }

        inline int y() { return (point & 0x00ff0000) >> 16; }

        inline int z() { return (point & 0x0000ffff); }

        inline coord under() { return coord(point - 1); }

        friend std::ostream& operator<<(ostream& os, coord& c) {
            return os << '{' << c.x() << ',' << c.y() << ',' << c.z() << '}';
        }

        bool operator<(const coord& rhs) const {
            return point < rhs.point;  // assume that you compare the record based on a
        }
    };

    struct brick {
        coord start, end;

        brick() {}

        brick(coord s, coord e) : start(s), end(e) {}

        friend std::ostream& operator<<(ostream& os, brick& c) { return os << c.start << '-' << c.end; }
    };

    bool can_fall(brick& b, set<coord>& occupied) {
        // on floor
        if (b.start.z() == 1 || b.end.z() == 1) {
            return false;
        }

        if (b.start.x() != b.end.x()) {
            for (int i = b.start.x(); i <= b.end.x(); i++) {
                coord u = coord(i, b.start.y(), b.start.z()).under();
                if (occupied.count(u)) {
                    return false;
                }
            }
        } else if (b.start.y() != b.end.y()) {
            for (int i = b.start.y(); i <= b.end.y(); i++) {
                coord u = coord(b.start.x(), i, b.start.z()).under();
                if (occupied.count(u)) {
                    return false;
                }
            }
        } else {
            coord u = coord(b.start.x(), b.start.y(), b.start.z()).under();
            if (occupied.count(u)) {
                return false;
            }
        }

        return true;
    }

    void move_brick(int index, vector<brick>& bricks, set<coord>& occupied) {
        brick b = bricks[index];

        if (b.start.x() != b.end.x()) {
            for (int i = b.start.x(); i <= b.end.x(); i++) {
                occupied.erase(coord(i, b.start.y(), b.start.z()));
                occupied.insert(coord(i, b.start.y(), b.start.z() - 1));
            }
        } else if (b.start.y() != b.end.y()) {
            for (int i = b.start.y(); i <= b.end.y(); i++) {
                occupied.erase(coord(b.start.x(), i, b.start.z()));
                occupied.insert(coord(b.start.x(), i, b.start.z() - 1));
            }
        } else {
            for (int i = b.start.z(); i <= b.end.z(); i++) {
                occupied.erase(coord(b.start.x(), b.start.y(), i));
                occupied.insert(coord(b.start.x(), b.start.y(), i - 1));
            }
        }
        bricks[index].start = coord(b.start.x(), b.start.y(), b.start.z() - 1);
        bricks[index].end = coord(b.end.x(), b.end.y(), b.end.z() - 1);
    }

    bool step(vector<brick>& bricks, set<coord>& occupied) {
        bool ret_value = false;

        int n_bricks = bricks.size();

        for (int i = 0; i < n_bricks; i++) {
            while (can_fall(bricks[i], occupied)) {
                ret_value = true;
                move_brick(i, bricks, occupied);
            }
        }

        return ret_value;
    }

    bool can_disintegrate(int index, vector<brick>& bricks, set<coord>& occupied) {
        set<coord> disintegrated;
        brick b = bricks[index];

        if (b.start.x() != b.end.x()) {
            for (int i = b.start.x(); i <= b.end.x(); i++) {
                disintegrated.insert(coord(i, b.start.y(), b.start.z()));
                occupied.erase(coord(i, b.start.y(), b.start.z()));
            }
        } else if (b.start.y() != b.end.y()) {
            for (int i = b.start.y(); i <= b.end.y(); i++) {
                disintegrated.insert(coord(b.start.x(), i, b.start.z()));
                occupied.erase(coord(b.start.x(), i, b.start.z()));
            }
        } else {
            for (int i = b.start.z(); i <= b.end.z(); i++) {
                disintegrated.insert(coord(b.start.x(), b.start.y(), i));
                occupied.erase(coord(b.start.x(), b.start.y(), i));
            }
        }

        bool ret_value = true;

        for (int i = 0; i < bricks.size(); i++) {
            if (i == index) continue;
            if (can_fall(bricks[i], occupied)) {
                ret_value = false;
                continue;
            }
        }
        for (auto it = disintegrated.begin(); it != disintegrated.end(); ++it) occupied.insert(*it);

        return ret_value;
    }

    int part1solution() override {
        string line;
        vector<brick> bricks;

        set<coord> occupied;

        while (getline(inputFile, line)) {
            auto brick_points = tokenize(line, '~');

            auto s = tokenize(brick_points[0], ',');
            auto e = tokenize(brick_points[1], ',');

            brick b;
            b.start = coord(stoi(s[0]), stoi(s[1]), stoi(s[2]));
            b.end = coord(stoi(e[0]), stoi(e[1]), stoi(e[2]));

            bricks.push_back(b);

            if (b.start.x() != b.end.x()) {
                for (int i = b.start.x(); i <= b.end.x(); i++) {
                    occupied.insert(coord(i, b.start.y(), b.start.z()));
                }
            } else if (b.start.y() != b.end.y()) {
                for (int i = b.start.y(); i <= b.end.y(); i++) {
                    occupied.insert(coord(b.start.x(), i, b.start.z()));
                }
            } else {
                for (int i = b.start.z(); i <= b.end.z(); i++) {
                    occupied.insert(coord(b.start.x(), b.start.y(), i));
                }
            }
        }

        // cout  << bricks.size() << ' ' << occupied.size() << endl;

        while (step(bricks, occupied)) {
        }

        int counter = 0;

        for (int i = 0; i < bricks.size(); i++) {
            // // cout  << bricks[i] << ": " << can_disintegrate(i,bricks, occupied) << endl;
            if (can_disintegrate(i, bricks, occupied)) {
                counter++;
            }
        }
        // cout  << bricks.size() << ' ' << occupied.size() << endl;

        return counter;
    }
    bool step_with_count(vector<brick>& bricks, set<coord>& occupied, vector<bool>& moved) {
        bool ret_value = false;

        int n_bricks = bricks.size();

        for (int i = 0; i < n_bricks; i++) {
            while (can_fall(bricks[i], occupied)) {
                ret_value = true;
                move_brick(i, bricks, occupied);
                moved[i] = true;
            }
        }

        return ret_value;
    }
    int destroy_and_count(int index, vector<brick> bricks, set<coord> occupied) {
        int counter = 0;
        brick b = bricks[index];

        bricks.erase(bricks.begin() + index);

        if (b.start.x() != b.end.x()) {
            for (int i = b.start.x(); i <= b.end.x(); i++) {
                occupied.erase(coord(i, b.start.y(), b.start.z()));
            }
        } else if (b.start.y() != b.end.y()) {
            for (int i = b.start.y(); i <= b.end.y(); i++) {
                occupied.erase(coord(b.start.x(), i, b.start.z()));
            }
        } else {
            for (int i = b.start.z(); i <= b.end.z(); i++) {
                occupied.erase(coord(b.start.x(), b.start.y(), i));
            }
        }
        vector<bool> moved(bricks.size());

        while (step_with_count(bricks, occupied, moved)) {
        }

        for (int i = 0; i < moved.size(); i++) {
            if (moved[i]) {
                counter++;
            }
        }

        return counter;
    }

    int part2solution() override {
        // Copy part 1 He
        string line;
        vector<brick> bricks;

        set<coord> occupied;

        while (getline(inputFile, line)) {
            auto brick_points = tokenize(line, '~');

            auto s = tokenize(brick_points[0], ',');
            auto e = tokenize(brick_points[1], ',');

            brick b;
            b.start = coord(stoi(s[0]), stoi(s[1]), stoi(s[2]));
            b.end = coord(stoi(e[0]), stoi(e[1]), stoi(e[2]));

            bricks.push_back(b);

            if (b.start.x() != b.end.x()) {
                for (int i = b.start.x(); i <= b.end.x(); i++) {
                    occupied.insert(coord(i, b.start.y(), b.start.z()));
                }
            } else if (b.start.y() != b.end.y()) {
                for (int i = b.start.y(); i <= b.end.y(); i++) {
                    occupied.insert(coord(b.start.x(), i, b.start.z()));
                }
            } else {
                for (int i = b.start.z(); i <= b.end.z(); i++) {
                    occupied.insert(coord(b.start.x(), b.start.y(), i));
                }
            }
        }

        // cout  << bricks.size() << ' ' << occupied.size() << endl;

        while (step(bricks, occupied)) {
        }

        int counter = 0;

        for (int i = 0; i < bricks.size(); i++) {
            int count = 0; 
            if (!can_disintegrate(i, bricks, occupied)) {
                count = destroy_and_count(i, bricks, occupied);
            }
            // cout  << i << ':' << count << endl;;
            counter += count;
        }

        // cout  << bricks.size() << ' ' << occupied.size() << endl;

        return counter;
    }
};