#pragma once
#include "../Day.h"
#include "../utils.h"

class Day_02 : public Day {
   public:
    Day_02() = default;

    Day_02(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_02/example.txt");
                break;

            case runType::input:
                inputFile.open("day_02/input.txt");
                break;
        }
    };

    enum Color {
        Blue,
        Red,
        Green,
    };

    int part1solution() override {
        string line;

        int sum = 0;
        int gameId = 1;

        while (getline(inputFile, line)) {
            bool possible = true;

            auto rounds = tokenize(line, ';');
            // print_vector(rounds);

            for (size_t i = 0; i < rounds.size(); i++) {
                auto grabs = tokenize(rounds[i], ' ');

                for (size_t j = 0; j < grabs.size(); j += 2) {
                    int balls = stoi(grabs[j]);

                    string color = grabs[j + 1];

                    if ((color == "blue" && balls > 14) || (color == "green" && balls > 13) ||
                        (color == "red" && balls > 12)) {
                        possible = false;
                        // cout << "'" << color << "' " << balls << "   " << endl << endl;
                        break;
                    }
                }
                if (!possible) break;
            }

            if (possible) {
                sum += gameId;
                // cout << "possible " << gameId << endl << endl;
            }

            gameId++;
        }

        return sum;
    }

    int part2solution() override {
        string line;

        int sum = 0;

        while (getline(inputFile, line)) {
            auto rounds = tokenize(line, ';');
            int min_red = 0, min_blue = 0, min_green = 0;

            for (size_t i = 0; i < rounds.size(); i++) {
                auto grabs = tokenize(rounds[i], ' ');

                for (size_t j = 0; j < grabs.size(); j += 2) {
                    int balls = stoi(grabs[j]);

                    string color = grabs[j + 1];

                    if (color == "blue") {
                        min_blue = max(balls, min_blue);
                    } else if (color == "green") {
                        min_green = max(balls, min_green);
                    } else if (color == "red") {
                        min_red = max(balls, min_red);
                    } else {
                        assert(0 && "Something went wrong");
                    }
                }

            }
            // cout << min_blue << " " << min_green << " " << min_red << endl;
            sum += min_blue * min_green * min_red;
        }

        return sum;
    }
};