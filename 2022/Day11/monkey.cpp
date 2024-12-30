#include <iostream>
#include <vector>
using namespace std;

extern long int modd;

class Monkey {
   public:
    vector<int> items;
    long int testValue;
    long int trueMonkey, falseMonkey;
    char op;
    long int opValue;
    long int inspects;

    Monkey(vector<int> i_items, long int i_testValue, long int i_trueMonkey,
           long int i_falseMonkey, char i_op, long int i_opValue) {
        this->items = i_items;
        this->testValue = i_testValue;
        this->trueMonkey = i_trueMonkey;
        this->falseMonkey = i_falseMonkey;
        this->op = i_op;
        this->opValue = i_opValue;
        inspects = 0;
    }
    ~Monkey() {}

    long int inspect() {
        long long currItem = this->items.at(0);
        inspects++;

        // cout << currItem << ' ';
        long long coefficent = this->opValue;
        if (coefficent == 0) coefficent = currItem;
        if (op == '*') {
            currItem = currItem * coefficent;
        } else {
            currItem = currItem + coefficent;
        }
        // cout << currItem << ' ';
        currItem = currItem % modd;

        // currItem /= 3;
        // cout << currItem << ' ';

        return currItem;
    }

    long int test(long int newValue) {
        if ((newValue % testValue) == 0) {
            return trueMonkey;
        } else {
            return falseMonkey;
        }
    }
};
