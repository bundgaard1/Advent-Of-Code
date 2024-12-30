// Advent of code 2022 - day
// Mathias Jørgensen
#include <assert.h>
#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

#define N 5000

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

void print_pairs(vector<pair<int, long long>> m) {
    for (int i = 0; i < m.size(); i++) {
        cout << "(" << m.at(i).first << "," << m.at(i).second << "), ";
    }
    cout << endl;
}
void print_list(vector<pair<int, long long>> m) {
    for (int i = 0; i < m.size(); i++) {
        cout << m.at(i).second << ", ";
    }
    cout << endl;
}

void swap_pair(vector<pair<int, long long>>* m, int a, int b) {
    // cout << a << ' ' << b << endl;
    assert(0 <= a && a < N && 0 <= b && b < N);
    pair<int, long long> temp = m->at(a);
    m->at(a) = m->at(b);
    m->at(b) = temp;
}

void grove_sum(vector<pair<int, long long>>* m) {
    int i;
    for (i = 0; i < N; i++) {
        if (m->at(i).second == 0) {
            break;
        }
    }
    long long a = m->at((i + 1000) % N).second;
    long long b = m->at((i + 2000) % N).second;
    long long c = m->at((i + 3000) % N).second;
    cout << a << " " << b << " " << c << endl;
    cout << "sum: " << a + b + c << endl;
}

int main(void) {
    ifstream inputFile;
    inputFile.open("input.txt");
    string line;

    vector<pair<int, long long>> nums;

    for (int i = 0; getline(inputFile, line); i++) {
        pair<int, long long> p = make_pair(i, stol(line));
        p.second = 811589153L * p.second;
        nums.push_back(p);
    }

    for (int k = 0; k < 10; k++) {
        /* code */

        for (int i = 0; i < N; i++) {
            int startIndex;
            for (startIndex = 0; startIndex < N; startIndex++) {
                if (nums.at(startIndex).first == i) break;
            }

            long long x = nums.at(startIndex).second;

            x %= (N - 1);

            if (x > 0) {
                int cur = startIndex;
                for (int swap = 0; swap < x; swap++) {
                    swap_pair(&nums, cur, (cur + 1) % N);
                    cur = (cur + 1) % N;
                }
            }
            if (x < 0) {
                int cur = startIndex;
                for (int swap = 0; swap > x; swap--) {
                    int b = (cur - 1) % N;
                    if (b < 0) b += N;
                    swap_pair(&nums, cur, b);
                    cur--;
                    if (cur < 0) cur += N;
                }
            }
        }
    }
    grove_sum(&nums);

    inputFile.close();

    return 0;
}
