// Advent of code 2022 - day
// Mathias Jørgensen
#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

char d2s[5] = {'=', '-', '0', '1', '2'};

vector<string> tokenize(string l, char tokenizer) {
    vector<string> tokens;
    stringstream check(l);

    string part;

    // Tokenizing w.r.t. space ' '
    while (getline(check, part, tokenizer)) {
        tokens.push_back(part);
    }

    return tokens;
}

long long StoL(string SNAFU) {
    long long n = 0;
    long long weight = 1;

    for (int i = SNAFU.size() - 1; i >= 0; i--) {
        long long a;
        char digit = SNAFU.at(i);
        if (digit == '-')
            a = -1;
        else if (digit == '=')
            a = -2;
        else
            a = digit - '0';

        n += a * weight;

        weight *= 5;
    }
    return n;
}

string intToSNAFU(long long a) {
    string SNAFU = "2-00=12=-00120000001";

    int r = 0;
    int count = 0;
    while (StoL(SNAFU) != a) {
        // add 1
        char* curr = &SNAFU.back();

        if (*curr == '2') {
            *curr = '=';
            r = 1;
        } else if (*curr == '0') {
            *curr = '1';
        } else if (*curr == '1') {
            *curr = '2';
        } else if (*curr == '-') {
            *curr = '0';
        } else if (*curr == '=') {
            *curr = '-';
        } else {
            cout << "mistake" << endl;
        }
        // ripple
        for (int i = SNAFU.size() - 2; i >= 0; i--) {
            if (r == 0) break;
            char* curr = &SNAFU.at(i);
            r = 0;
            if (*curr == '2') {
                *curr = '=';
                r = 1;
            } else if (*curr == '0') {
                *curr = '1';
            } else if (*curr == '1') {
                *curr = '2';
            } else if (*curr == '-') {
                *curr = '0';
            } else if (*curr == '=') {
                *curr = '-';
            } else {
                cout << "mistake" << endl;
            }
        }
        if (count == 10000000) {
            count = 0;
            cout << SNAFU << " - ";
            cout << "distance: " << a - StoL(SNAFU) << endl;
        }
        count++;
    }
    cout << SNAFU << " - " << StoL(SNAFU) << " - " << a << endl;

    return SNAFU;
}

string smartItoS(long long n) {
    string res = "";
    while (n > 0) {
        int d = ((n + 2) % 5);
        res.push_back(d2s[d]);
        n -= d + 2;
        n /= 5;
    }
    return res;
}

int main(void) {
    ifstream inputFile;
    inputFile.open("input.txt");
    string line;

    long long sum = 0;

    while (getline(inputFile, line)) sum += StoL(line);

    cout << sum << endl;

    string answer = smartItoS(sum);

    cout << answer << endl << StoL(answer);

    inputFile.close();

    return 0;
}