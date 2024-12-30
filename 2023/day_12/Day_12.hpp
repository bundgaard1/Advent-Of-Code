#pragma once
#include "../Day.h"
#include "../utils.h"
using namespace std;

class Day_12 : public Day {
   public:
    Day_12() = default;

    Day_12(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_12/example.txt");
                break;

            case runType::input:
                inputFile.open("day_12/input.txt");
                break;
        }
        search_calls = 0;
    };
    int search_calls;

    bool arrangement_is_valid(const string& arrange, const vector<int>& groups) {
        // // cout  << arrange << endl;
        int curr_group_size = 0;
        int idx = 0;
        int group_size = groups.size();

        for (int i = 0; i < arrange.length(); i++) {
            if (arrange[i] == '#') {
                curr_group_size++;

                if (idx >= group_size || curr_group_size > groups[idx]) return false;
            } else {
                if (curr_group_size != 0) {
                    if (idx >= group_size || groups[idx] != curr_group_size) return false;
                    idx++;
                }
                curr_group_size = 0;
            }
        }

        if (curr_group_size != 0) {
            return groups[idx] == curr_group_size;
        }

        return true;
    }

    // Part 1 is all myself!!
    int part1solution() override {
        string line;

        int sum = 0;

        int idx = 0;

        while (getline(inputFile, line)) {
            // // cout  << line;

            auto tokens = tokenize(line, ' ');

            string record = tokens[0];
            vector<string> groups_string = tokenize(tokens[1], ',');

            vector<int> groups;
            for (auto s : groups_string) {
                groups.push_back(stoi(s));
            }

            int damaged = 0;
            vector<int> unknown;

            for (size_t i = 0; i < line.size(); i++) {
                switch (line[i]) {
                    case '?':
                        unknown.push_back(i);
                        break;
                    case '#':
                        damaged++;
                        break;

                    default:
                        break;
                }
            }

            int num_unknowns = unknown.size();
            int need_damaged = accumulate(groups.begin(), groups.end(), 0);
            int count = 0;

            for (size_t i = 0; i < 1 << num_unknowns; i++) {
                string curr_check = record;

                int new_damaged = 0;
                for (int un = 0; un < unknown.size(); un++) {
                    int idx = unknown[un];

                    if ((i >> un) & 1) {
                        curr_check[idx] = '#';
                        new_damaged++;
                    } else {
                        curr_check[idx] = '.';
                    }
                }

                if (new_damaged + damaged == need_damaged) {
                    if (arrangement_is_valid(curr_check, groups)) {
                        count++;
                    }
                }
            }

            sum += count;
            // // cout  << idx++ << ": " << count << endl;
        }

        return sum;
    }



    int64_t search(string& s, vector<int64_t>& groups, int i, int curlen, map<int64_t, int64_t>& dp) {
        //// cout  << s << " i:" << i << "  " << s[i] << "  curlen:" << curlen << "  ";
        //print_vector(groups, 1);

        search_calls++;
        int64_t key = ((accumulate(groups.begin(), groups.end(), 0)) << 16) + (i << 8) + (curlen);
        int exists = dp.count(key);
        if (exists == 1) {
            return dp[key];
        }

        if (!groups.empty() && curlen > groups[0]) return false;

        if (i == s.length()) {
            if ((groups.empty() && curlen == 0) || (groups.size() == 1 && groups[0] == curlen)) {
                // // cout  << "yes" << endl;
                return 1;
            }
            // // cout  << "no" << endl;
            return 0;
        }

        int64_t total = 0;

        if (s[i] == '.') {
            if (curlen == 0) {
                total += search(s, groups, i + 1, 0, dp);
            } else if (!groups.empty() && groups[0] == curlen) {
                vector<int64_t> new_groups(groups.begin() + 1, groups.end());
                total += search(s, new_groups, i + 1, 0,   dp );
            }
        } else if (s[i] == '#') {
            total += search(s, groups, i + 1, curlen + 1, dp);

        } else {  // We have a '?'

            total += search(s, groups, i + 1, curlen + 1, dp);

            // // put '.', prevoiusly had a '.'
            if (curlen == 0) {
                total += search(s, groups, i + 1, 0, dp);
            } else if (!groups.empty() && groups[0] == curlen) {
                vector<int64_t> new_groups(groups.begin() + 1, groups.end());
                total += search(s, new_groups, i + 1, 0, dp);
            }
        }

        //// cout  << "Inserted " << key << endl;

        dp.insert(pair<int64_t, int64_t>(key,total));
        return total;
    }


    // Needed help for the recursive-search function, had trouble wrapping my dumb read around it,
    // But i implemented the memoization myself.

    int part2solution() override {
        string line;

        int64_t sum = 0;

        while (getline(inputFile, line)) {
            auto tokens = tokenize(line, ' ');

            string r = tokens[0];
            string record = r + '?' + r + '?' + r + '?' + r + '?' + r;
            // // cout  << record << "   ";

            vector<string> groups_string = tokenize(tokens[1], ',');
            vector<int64_t> groups;
            for (int i = 0; i < 5; i++) {
                for (auto s : groups_string) {
                    groups.push_back(stoll(s));
                }
            }
            // print_vector(groups, 1);

            map<int64_t, int64_t> dp;

            int64_t count = search(record, groups, 0, 0, dp);
            sum += count;

            // cout  << count << endl;
        }

        // cout  << "Part 2: " << sum << endl;
        // cout  << "Search calls: " << search_calls << endl;

        return -1;
    }
};