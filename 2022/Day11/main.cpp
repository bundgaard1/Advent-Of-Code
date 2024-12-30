// Advent of code 2022 - day 1
// Mathias Jørgensen
#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
#include <vector>

static long int modd = 1;
#include "monkey.cpp"
using namespace std;

void print_monkeys(vector<Monkey> m);
void print_worry(vector<Monkey> m);

int main(void) {
    vector<Monkey> monkeys;

    monkeys.push_back(Monkey({93, 54, 69, 66, 71}, 7, 7, 1, '*', 3));
    monkeys.push_back(Monkey({89, 51, 80, 66}, 19, 5, 7, '*', 17));
    monkeys.push_back(Monkey({90, 92, 63, 91, 96, 63, 64}, 13, 4, 3, '+', 1));
    monkeys.push_back(Monkey({65, 77}, 3, 4, 6, '+', 2));
    monkeys.push_back(Monkey({76, 68, 94}, 2, 0, 6, '*', 0));
    monkeys.push_back(Monkey({86, 65, 66, 97, 73, 83}, 11, 2, 3, '+', 8));
    monkeys.push_back(Monkey({78}, 17, 0, 1, '+', 6));
    monkeys.push_back(
        Monkey({89, 57, 59, 61, 87, 55, 55, 88}, 5, 2, 5, '+', 7));

    // Find booster
    for (int i = 0; i < monkeys.size(); i++) {
        modd *= monkeys.at(i).testValue;
    }
    cout << modd << endl;

    for (int round = 1; round <= 10000; round++) {
        for (int i = 0; i < monkeys.size(); i++) {
            while (!monkeys.at(i).items.empty()) {
                long int newValue = monkeys.at(i).inspect();
                long int reciveMonkey = monkeys.at(i).test(newValue);
                // cout << reciveMonkey << endl;
                monkeys.at(i).items.erase(monkeys.at(i).items.begin());
                monkeys.at(reciveMonkey).items.push_back(newValue);
            }
        }
        cout << "Round " << round << endl;
        // print_monkeys(monkeys);
    }
    print_monkeys(monkeys);
    cout << endl;
    print_worry(monkeys);
}

void print_monkeys(vector<Monkey> m) {
    for (int i = 0; i < m.size(); i++) {
        cout << "Monkey " << i << ": ";
        Monkey curr = m.at(i);
        for (int j = 0; j < curr.items.size(); j++) {
            cout << m.at(i).items.at(j) << ", ";
        }
        cout << endl;
    }
}
void print_worry(vector<Monkey> m) {
    for (int i = 0; i < m.size(); i++) {
        cout << "Monkey " << i << ": " << m.at(i).inspects << endl;
    }
    cout << endl;
}
