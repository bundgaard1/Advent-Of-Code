#pragma once

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <queue>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <numeric>
#include <tuple>
#include <bitset>
using namespace std;

template <typename T>
void print_vector(const vector<T>& v, bool newline = 0) {
    //cout << "{";
    for (T a : v) {
      //  cout << a << ", ";
    }
    //cout << "}";
    if (newline) {
        //cout << endl;
    }
}

vector<string> tokenize(const string& l, char tokenizer) {
    vector<string> tokens;
    stringstream check(l);
    string part;
    while (getline(check, part, tokenizer)) {
        if (part.size() == 0) continue;

        tokens.push_back(part);
    }
    return tokens;
}


