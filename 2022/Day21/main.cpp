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

static vector<pair<string, string>> yell;

bool is_number(const char c) { return c >= '0' && c <= '9'; }

long long evaluate(string exp) {
    if (is_number(exp.at(0))) return stoll(exp);

    // cout << exp << endl;

    vector<string> tokens = tokenize(exp, ' ');
    string left = tokens.at(0);
    char op = tokens.at(1).at(0);
    string right = tokens.at(2);

    int leftIdx;
    for (int i = 0; i < yell.size(); i++) {
        if (yell.at(i).first == left) {
            leftIdx = i;
            break;
        }
    }

    int rightIdx;
    for (int i = 0; i < yell.size(); i++) {
        if (yell.at(i).first == right) {
            rightIdx = i;
            break;
        }
    }

    long long a = evaluate(yell.at(leftIdx).second);
    long long b = evaluate(yell.at(rightIdx).second);
    // cout << a << " " << op << " " << b << " = ";

    switch (op) {
        case '+':
            // cout << a + b << endl;
            if (exp == "fzvp + grlb") {
                // cout << a << " " << b << endl;
                return a - b;
            }

            return a + b;
            break;
        case '-':
            // cout << a - b << endl;
            return a - b;
            break;
        case '*':
            // cout << a * b << endl;
            return a * b;
            break;
        case '/':
            // cout << a / b << endl;
            return a / b;
            break;
        default:
            cout << "WTF";
            break;
    }

    return 1;
}

int main(void) {
    ifstream inputFile;
    inputFile.open("input.txt");
    string line;

    for (int i = 0; getline(inputFile, line); i++) {
        vector<string> tokens = tokenize(line, ':');
        pair<string, string> p = make_pair(tokens.at(0), tokens.at(1));
        yell.push_back(p);
    }

    int rootIdx;
    for (int i = 0; i < yell.size(); i++) {
        if (yell.at(i).first == "root") {
            rootIdx = i;
            break;
        }
    }

    int humnIdx;
    for (int i = 0; i < yell.size(); i++) {
        if (yell.at(i).first == "humn") {
            humnIdx = i;
            break;
        }
    }
    long long est = 3700000000000;
    long long radix = 100000000000;
    int k = 0;
    long long result = evaluate(yell.at(rootIdx).second);
    while (result != 0) {
        yell.at(humnIdx).second = to_string(est);

        result = evaluate(yell.at(rootIdx).second);
        cout << est << ": " << result << endl;

        if (result < 0) {
            est -= radix;
        }
        if (result > 0) {
            est += radix;
        }
        if (k > 10) {
            radix = radix /= 10;
            k = 0;
        } else {
            k++;
        }
    }

    inputFile.close();

    return 0;
}
