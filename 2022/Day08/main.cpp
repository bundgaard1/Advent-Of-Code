// Advent of code 2022 - day 1
// Mathias Jørgensen
#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

bool is_visible(vector<vector<int>>, int, int);
int scenic_score(vector<vector<int>>, int, int);

int main(void) {
    ifstream inputFile;
    inputFile.open("input.txt");
    string line;

    vector<vector<int>> forest;

    vector<vector<bool>> visible;

    vector<vector<int>> scenicScore;

    while (getline(inputFile, line)) {
        forest.push_back({});
        visible.push_back({});
        scenicScore.push_back({});
        for (int i = 0; i < line.size(); i++) {
            forest.back().push_back(line.at(i) - '0');
            visible.back().push_back(false);
            scenicScore.back().push_back(1);
        }
    }

    for (int i = 0; i < forest.size(); i++) {
        for (int j = 0; j < forest.at(i).size(); j++) {
            cout << forest.at(i).at(j);
        }
        cout << "\n";
    }

    for (int i = 0; i < visible.size(); i++) {
        for (int j = 0; j < visible.at(i).size(); j++) {
            visible[i][j] = is_visible(forest, i, j);
            cout << visible[i][j] << " ";
        }
        cout << "\n";
    }

    int total_visible = 0;
    for (int i = 0; i < visible.size(); i++) {
        for (int j = 0; j < visible.at(i).size(); j++) {
            if (visible[i][j]) total_visible++;
        }
    }

    cout << "Total Visible: " << total_visible << endl;

    int bestScore = 0;

    for (int i = 0; i < scenicScore.size(); i++) {
        for (int j = 0; j < scenicScore.at(i).size(); j++) {
            scenicScore.at(i).at(j) = scenic_score(forest, i, j);
            if (scenicScore.at(i).at(j) > bestScore) {
                bestScore = scenicScore.at(i).at(j);
            }
            cout << scenicScore.at(i).at(j) << " ";
        }
        cout << "\n";
    }

    cout << "Best score: " << bestScore << endl;

    inputFile.close();
    return 0;
}

bool is_visible(vector<vector<int>> f, int row, int col) {
    if (row == 0 || col == 0 || row == f.size() - 1 ||
        col == f.at(0).size() - 1) {
        return true;
    }

    int tree_height = f.at(row).at(col);

    bool covered[4] = {false};
    // above
    for (int i = row - 1; i >= 0; i--) {
        int compare_height = f.at(i).at(col);
        if (compare_height >= tree_height) {
            covered[0] = true;
            break;
        }
    }

    // below
    for (int i = row + 1; i < f.size(); i++) {
        int compare_height = f.at(i).at(col);
        if (compare_height >= tree_height) {
            covered[1] = true;
            break;
        }
    }

    // left
    for (int i = col - 1; i >= 0; i--) {
        int compare_height = f.at(row).at(i);
        if (compare_height >= tree_height) {
            covered[2] = true;
            break;
        }
    }

    // right
    for (int i = col + 1; i < f.at(0).size(); i++) {
        int compare_height = f.at(row).at(i);
        if (compare_height >= tree_height) {
            covered[3] = true;
            break;
        }
    }
    if (covered[0] && covered[1] && covered[2] && covered[3]) {
        return false;
    } else {
        return true;
    }
}

int scenic_score(vector<vector<int>> f, int row, int col) {
    if (row == 0 || col == 0 || row == f.size() - 1 ||
        col == f.at(0).size() - 1) {
        return 0;
    }

    int tree_height = f.at(row).at(col);

    int distance[4] = {1, 1, 1, 1};
    // above
    for (int i = row - 1; i >= 0; i--) {
        int compare_height = f.at(i).at(col);
        if (compare_height >= tree_height || i == 0) {
            distance[0] = row - i;
            break;
        }
    }

    // below
    for (int i = row + 1; i < f.size(); i++) {
        int compare_height = f.at(i).at(col);
        if (compare_height >= tree_height || i == f.size() - 1) {
            distance[1] = i - row;
            break;
        }
    }

    // left
    for (int i = col - 1; i >= 0; i--) {
        int compare_height = f.at(row).at(i);
        if (compare_height >= tree_height || i == 0) {
            distance[2] = col - i;
            break;
        }
    }

    // right
    for (int i = col + 1; i < f.at(row).size(); i++) {
        int compare_height = f.at(row).at(i);
        if (compare_height >= tree_height || i == f.at(row).size() - 1) {
            distance[3] = i - col;
            break;
        }
    }
    int product = 1;
    for (int i = 0; i < 4; i++) {
        product *= distance[i];
    }
    return product;
}
