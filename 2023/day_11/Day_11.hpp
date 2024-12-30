#pragma once
#include "../Day.h"
#include "../utils.h"

class Day_11 : public Day {
   public:
    Day_11() = default;

    Day_11(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_11/example.txt");
                break;

            case runType::input:
                inputFile.open("day_11/input.txt");
                break;
        }
    };

    struct point {
        int64_t x;
        int64_t y;
        point(int64_t _x, int64_t _y) : x(_x), y(_y) {}

        int64_t manhattan_dist(const point& other) {
            int64_t dx = abs(x - other.x);
            int64_t dy = abs(y - other.y);
            return dx + dy;
        }

        int64_t space_dist(const point& other, vector<int64_t>& empty_rows, vector<int64_t>& empty_cols,
                           int64_t multiplier) {
            int64_t dist = this->manhattan_dist(other);

            for (auto i : empty_cols) {
                if ((x < i && i < other.x) || (other.x < i && i < x)) dist += (multiplier - 1);
            }

            for (auto i : empty_rows) {
                if ((y < i && i < other.y) || (other.y < i && i < y)) dist += (multiplier - 1);
            }

            return dist;
        }
    };

    int part1solution() override {
        string line;

        vector<string> image;

        while (getline(inputFile, line)) {
            image.push_back(line);
        }

        // vertical
        for (size_t i = 0; i < image.size(); i++) {
            bool no_galax = all_of(image[i].begin(), image[i].end(), [](char c) { return c == '.'; });
            if (no_galax) {
                string new_line = image[i];
                image.emplace(image.begin() + i, new_line);
                i++;
            }
        }

        // horizontal
        for (size_t i = 0; i < image[0].length(); i++) {
            bool no_galax = true;
            for (int j = 0; j < image.size(); j++) {
                if (image[j][i] == '#') {
                    no_galax = false;
                    break;
                }
            }

            if (no_galax) {
                for (int j = 0; j < image.size(); j++) {
                    image[j].insert(i, ".");
                }
                i++;
            }
        }

        // for_each(image.begin(), image.end(), [](string& s) { // cout  << s << endl; });

        vector<point> galaxies;
        int idy = 0;

        for_each(image.begin(), image.end(), [&idy, &galaxies](string& row) {
            int idx = 0;
            for_each(row.begin(), row.end(), [&idx, &idy, &galaxies](char c) {
                if (c == '#') {
                    galaxies.push_back(point(idx, idy));
                }
                idx++;
            });

            idy++;
        });

        // for_each(galaxies.begin(), galaxies.end(), [](point p) { // cout  << "(" << p.x << ", " << p.y << ")" << endl;
        // });

        int n = galaxies.size();

        int sum = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                sum += galaxies[i].manhattan_dist(galaxies[j]);
            }
        }

        return sum;
    }

    /*  int part2solution() override {
         string line;

         vector<string> image;

         int64_t multiplier = 1000000;

         while (getline(inputFile, line)) {
             image.push_back(line);
         }

         vector<int64_t> x_dists(image[0].length(), multiplier);
         vector<int64_t> y_dists(image.size(), multiplier);

         vector<point> galaxies;

         for (int idy = 0; idy < image.size(); idy++) {
             int n = image[0].length();
             for (int idx = 0; idx < n; idx++) {
                 char c = image[idy][idx];
                 if (c == '#') {
                     galaxies.push_back(point(idx, idy));
                     x_dists[idx] = 1;
                     y_dists[idy] = 1;
                 }
             }
         }

         for (int i = 1; i < x_dists.size(); i++) {
             x_dists[i] = x_dists[i] + x_dists[i - 1];
         }

         for (int i = 1; i < y_dists.size(); i++) {
             y_dists[i] = y_dists[i] + y_dists[i - 1];
         }

         int n = galaxies.size();

         int64_t sum = 0;

         for (int i = 0; i < n; i++) {
             for (int j = i + 1; j < n; j++) {
                 int64_t dx = abs(x_dists[galaxies[i].x] - x_dists[galaxies[j].x]);
                 int64_t dy = abs(y_dists[galaxies[i].y] - y_dists[galaxies[j].y]);
                 sum += dx + dy;
             }
         }
         // cout  << sum << endl;

         return sum;
     } */

    int part2solution() override {
        string line;

        vector<string> image;

        while (getline(inputFile, line)) {
            image.push_back(line);
        }

        vector<int64_t> empty_rows;
        vector<int64_t> empty_cols;

        // rows
        for (size_t i = 0; i < image.size(); i++) {
            bool no_galax = all_of(image[i].begin(), image[i].end(), [](char c) { return c == '.'; });
            if (no_galax) {
                empty_rows.push_back(i);
            }
        }

        // cols
        for (size_t i = 0; i < image[0].length(); i++) {
            bool no_galax = true;
            for (int j = 0; j < image.size(); j++) {
                if (image[j][i] == '#') {
                    no_galax = false;
                    break;
                }
            }

            if (no_galax) {
                empty_cols.push_back(i);
            }
        }

        vector<point> galaxies;
        int idy = 0;

        for_each(image.begin(), image.end(), [&idy, &galaxies](string& row) {
            int idx = 0;
            for_each(row.begin(), row.end(), [&idx, &idy, &galaxies](char c) {
                if (c == '#') {
                    galaxies.push_back(point(idx, idy));
                }
                idx++;
            });

            idy++;
        });

        for_each(empty_cols.begin(), empty_cols.end(), [](int p) { // cout  << p << " "; 
        });
        // cout  << endl;
        for_each(empty_rows.begin(), empty_rows.end(), [](int p) { // cout  << p << " "; 
        });
        // cout  << endl;

        int n = galaxies.size();

        int64_t sum = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                sum += galaxies[i].space_dist(galaxies[j], empty_rows, empty_cols, 1000000);
            }
        }

        // cout  << sum << endl;

        return sum;
    }
};