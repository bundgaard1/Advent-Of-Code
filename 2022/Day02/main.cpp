// Advent of code 2022 - day 2
// Mathias Jørgensen
#include <fstream>
#include <iostream>

#define ARRAY_SIZE 500

using namespace std;

// X = lose
// Y = draw
// Z = win

int scoreRound(char opp, char res) {
    int score = 0;
    switch (opp) {
        // ROCK
        case 'A':
            switch (res) {
                case 'X':
                    score += 0;  // lose
                    score += 3;  // scissors
                    break;
                case 'Y':
                    score += 3;  // draw
                    score += 1;  // rock
                    break;
                case 'Z':
                    score += 6;  // win
                    score += 2;  // paper
                    break;
                default:
                    break;
            }
            break;
        // PAPER
        case 'B':
            switch (res) {
                case 'X':
                    score += 0;  // lose
                    score += 1;  // rock
                    break;
                case 'Y':
                    score += 3;  // draw
                    score += 2;  // paper
                    break;
                case 'Z':
                    score += 6;  // win
                    score += 3;  // scissors
                    break;
                default:
                    break;
            }
            break;
        // SCISSORS
        case 'C':
            switch (res) {
                case 'X':
                    score += 0;  // lose
                    score += 2;  // paper
                    break;
                case 'Y':
                    score += 3;  // draw
                    score += 3;  // scissors
                    break;
                case 'Z':
                    score += 6;  // win
                    score += 1;  // rock
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }

    return score;
}

int main(void) {
    ifstream inputFile;
    inputFile.open("input.txt");

    string line;
    int total_score = 0;

    while (getline(inputFile, line)) {
        int roundScore = scoreRound(line[0], line[2]);
        total_score += roundScore;
    }

    cout << "Total score: " << total_score << endl;

    inputFile.close();
    return 0;
}
