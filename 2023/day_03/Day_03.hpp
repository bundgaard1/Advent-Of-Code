#pragma once
#include "../Day.h"
#include "../utils.h"

class Day_03 : public Day {
   public:
    Day_03() = default;

    Day_03(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_03/example.txt");
                break;

            case runType::input:
                inputFile.open("day_03/input.txt");
                break;
        }
    };

    bool is_symbol(char c) { return !(isdigit(c) || c == '.'); }

    int part_number(const string& line, int pos, int line_num, set<pair<int, int>>& coord_set) {
        int start = pos, end = pos;

        while (start > 0) {
            if (isdigit(line[start - 1])) {
                start--;
            } else {
                break;
            }
        }

        while (end < line.length() - 1) {
            if (isdigit(line[end + 1])) {
                end++;
            } else {
                break;
            }
        }

        int mult = 1;

        int number = 0;

        for (int i = end; i >= start; i -= 1) {
            number += (line[i] - '0') * mult;
            mult *= 10;
            coord_set.emplace(pair<int, int>(i, line_num));
        }

        // cout << number << endl;

        return number;
    }

    int part1solution() override {
        string line;
        vector<string> schematic;

        set<pair<int, int>> coord_set;

        while (getline(inputFile, line)) {
            schematic.push_back(line);
        }

        int sum = 0;

        for (size_t i = 0; i < schematic.size(); i++) {
            string curr_string = schematic.at(i);
            for (size_t j = 0; j < schematic.size(); j++) {
                if (is_symbol(curr_string.at(j))) {
                    // cout << curr_string.at(j) << ": " << endl;
                    for (int dy = -1; dy <= 1; dy++) {
                        for (int dx = -1; dx <= 1; dx++) {
                            if ((dy == 0 && dx == 0) || i + dy < 0 || i + dy >= schematic.size() || j + dx < 0 ||
                                j + dx > curr_string.length())
                                continue;

                            if (isdigit(schematic[i + dy][j + dx])) {
                                if (coord_set.count(pair<int, int>(j + dx, i + dy))) continue;
                                int start = j + dx;
                                int end = j + dx;
                                string line = schematic.at(i + dy);

                                while (start > 0) {
                                    if (isdigit(line[start - 1])) {
                                        start--;
                                    } else {
                                        break;
                                    }
                                }

                                while (end < (line.length() - 1)) {
                                    if (isdigit(line[end + 1])) {
                                        end++;
                                    } else {
                                        break;
                                    }
                                }

                                int mult = 1;

                                int number = 0;

                                for (int m = end; m >= start; m -= 1) {
                                    number += (line[m] - '0') * mult;
                                    mult *= 10;
                                    coord_set.emplace(pair<int, int>(m, i + dy));
                                }

                                // cout << number << endl;

                                sum += number;
                            }
                        }
                    }
                }
            }
        }

        return sum;
    }

    int part2solution() override {
        string line;
        vector<string> schematic;

        set<pair<int, int>> coord_set;

        while (getline(inputFile, line)) {
            schematic.push_back(line);
        }

        long long sum = 0;

        for (size_t i = 0; i < schematic.size(); i++) {
            string curr_string = schematic.at(i);
            for (size_t j = 0; j < schematic.size(); j++) {
                if (curr_string.at(j) == '*') {
                    vector<int> gear_numbers;
                    // cout << curr_string.at(j) << ": " << endl;
                    for (int dy = -1; dy <= 1; dy++) {
                        for (int dx = -1; dx <= 1; dx++) {
                            if ((dy == 0 && dx == 0) || i + dy < 0 || i + dy >= schematic.size() || j + dx < 0 ||
                                j + dx > curr_string.length())
                                continue;

                            if (isdigit(schematic[i + dy][j + dx])) {
                                if (coord_set.count(pair<int, int>(j + dx, i + dy))) continue;
                                int start = j + dx;
                                int end = j + dx;
                                string line = schematic.at(i + dy);

                                while (start > 0) {
                                    if (isdigit(line[start - 1])) {
                                        start--;
                                    } else {
                                        break;
                                    }
                                }

                                while (end < (line.length() - 1)) {
                                    if (isdigit(line[end + 1])) {
                                        end++;
                                    } else {
                                        break;
                                    }
                                }

                                int mult = 1;

                                int number = 0;

                                for (int m = end; m >= start; m -= 1) {
                                    number += (line[m] - '0') * mult;
                                    mult *= 10;
                                    coord_set.emplace(pair<int, int>(m, i + dy));
                                }

                                gear_numbers.push_back(number);
                            }
                        }
                    }
                    if (gear_numbers.size() == 2) {
                        int number = gear_numbers[0] * gear_numbers[1];

                        sum += number;
                    }
                }
            }
        }

        return sum;
    }
};