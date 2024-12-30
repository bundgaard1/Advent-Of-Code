#pragma once
#include "../Day.h"
#include "../utils.h"

class Day_04 : public Day {
   public:
    Day_04() = default;

    Day_04(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_04/example.txt");
                break;

            case runType::input:
                inputFile.open("day_04/input.txt");
                break;
        }
    };

    int part1solution() override {
        string line;

        int sum = 0;

        while (getline(inputFile, line)) {
            auto parts = tokenize(line, '|');

            set<int> winning;

            int total_winning = 0;

            auto winning_strings = tokenize(parts[0], ' ');
            print_vector(winning_strings);
            for (auto num_s : winning_strings) {
                winning.emplace(stoi(num_s));
            }

            auto numbers = tokenize(parts[1], ' ');
            print_vector(numbers);
            for (auto num_s : numbers) {
                int num = stoi(num_s);
                if (winning.count(num)) {
                    total_winning++;
                }
            }
            // cout << "Total winning numbers: " << total_winning << endl;

            if (total_winning == 0) continue;

            sum += (1 << (total_winning - 1));
        }

        return sum;
    }

    int part2solution() override {
        string line;
        int total_cards = 205;

        map<int, int> instances;

        for (int i = 1; i <= total_cards; i++)
        {
            instances[i] = 1;
        }
        

        int card_num = 1;

        while (getline(inputFile, line)) {
            auto parts = tokenize(line, '|');

            set<int> winning;

            int total_winning = 0;

            auto winning_strings = tokenize(parts[0], ' ');
            // print_vector(winning_strings);
            for (auto num_s : winning_strings) {
                winning.emplace(stoi(num_s));
            }

            auto numbers = tokenize(parts[1], ' ');
            // print_vector(numbers);
            for (auto num_s : numbers) {
                int num = stoi(num_s);
                if (winning.count(num)) {
                    total_winning++;
                }
            }
            // cout << "CARD: " << card_num << " - Total winning numbers: " << total_winning << endl;

            int multiplier = instances[card_num];
            for (int i = 1; i <= total_winning; i++)
            {
                instances[card_num + i] += multiplier;
            }
            
            card_num++;
        }

        int sum = 0;

        for (int i = 1; i <= total_cards; i++)
        {
            // cout << instances[i] << endl;
            sum += instances[i];
        }
        

        return sum;
    }
};