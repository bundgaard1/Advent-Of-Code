// Advent of code 2022 - day 3
// Mathias Jørgensen
#include <stdlib.h>

#include <fstream>
#include <iostream>

using namespace std;

int charToItem(char c) {
    if (isupper(c)) {
        return (int)c - 38;
    } else {
        return (int)c - 96;
    }
}

int main(int argc, char const *argv[]) {
    ifstream inputFile;
    inputFile.open("input.txt");

    static string line;

    int part1sum = 0;
    int part2sum = 0;

    for (int group = 0; group < 100; group++) {
        /* code */
        bool common1[53] = {false};
        bool common2[53] = {false};
        int commonItem;

        for (int member = 0; member < 3; member++) {
            getline(inputFile, line);
            bool contains[53] = {false};
            cout << line << endl;

            int length = line.length();
            string firstHalf = line.substr(0, length / 2);
            string secondHalf = line.substr(length / 2, length);

            // cout << firstHalf << endl << secondHalf << endl;

            for (char c : firstHalf) {
                int item = charToItem(c);
                contains[item] = true;
            }
            int dublicate;

            for (char c : secondHalf) {
                int item = charToItem(c);
                // cout << item << endl;
                if (contains[item] == true) {
                    dublicate = item;
                }
            }
            part1sum += dublicate;

            // cout << dublicate << endl << endl;

            for (char c : line) {
                int item = charToItem(c);
                if (member == 0) {
                    common1[item] = true;
                } else if (member == 1) {
                    common2[item] = true;
                } else {
                    if (common1[item] && common2[item]) {
                        commonItem = item;
                    }
                }
            }
        }

        cout << "Common item: " << commonItem << endl << endl;
        part2sum += commonItem;
    }

    cout << "Part 1 sum: " << part1sum << endl;
    cout << "Part 2 sum: " << part2sum;

    inputFile.close();
    return 0;
}