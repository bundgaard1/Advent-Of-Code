#pragma once
#include "../Day.h"
#include "../utils.h"

class Day_19 : public Day {
   public:
    Day_19() = default;

    Day_19(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_19/example.txt");
                break;

            case runType::input:
                inputFile.open("day_19/input.txt");
                break;
        }
    };

    struct rule {
        char cat;
        bool greater_than;
        int number;
        string next;
    };

    int part1solution() override {
        string line;

        map<string, vector<rule>> workflows;

        while (getline(inputFile, line)) {
            if (line == "") break;

            auto workflow_parts = tokenize(line, ' ');

            string name = workflow_parts[0];

            workflows[name] = vector<rule>();

            auto new_rules = tokenize(workflow_parts[1], ',');

            for (int i = 0; i < new_rules.size(); i++) {
                string new_rule_str = new_rules[i];

                rule new_rule;
                if (i == new_rules.size() - 1) {
                    new_rule.next = new_rule_str;
                } else {
                    new_rule.cat = new_rule_str[0];

                    new_rule.greater_than = new_rule_str[1] == '>' ? true : false;

                    auto found = new_rule_str.find(':', 0);
                    new_rule.number = stoi(string(new_rule_str.begin() + 2, new_rule_str.begin() + found));

                    new_rule.next = string(new_rule_str.begin() + found + 1, new_rule_str.end());
                }

                // // cout  << new_rule.cat << " " << new_rule.greater_than << " " << new_rule.number << " " <<
                // new_rule.next
                //      << endl;

                workflows[name].push_back(new_rule);
            }
            // // cout  << endl;
        }

        int sum = 0;

        while (getline(inputFile, line)) {
            auto parts_ratings = tokenize(line, ',');
            int x = stoi(parts_ratings[0]);
            int m = stoi(parts_ratings[1]);
            int a = stoi(parts_ratings[2]);
            int s = stoi(parts_ratings[3]);

            // // cout  << x << " " << m << " " << a << " " << s << endl;

            string next_wf = "in";

            while (true) {
                if (next_wf == "A" || next_wf == "R") break;

                // // cout  << next_wf << "->";

                vector<rule> wf_rules = workflows[next_wf];

                for (int i = 0; i < wf_rules.size(); i++) {
                    rule r = wf_rules[i];

                    if (i == wf_rules.size() - 1) {
                        next_wf = r.next;
                        break;
                    }
                    int part_rating = r.cat == 'x' ? x : r.cat == 'm' ? m : r.cat == 'a' ? a : s;

                    bool rule_ture;

                    if (r.greater_than) {
                        rule_ture = part_rating > r.number;
                    } else {
                        rule_ture = part_rating < r.number;
                    }

                    if (rule_ture) {
                        next_wf = r.next;
                        break;
                    } else {
                        continue;
                    }
                }
            }
            if (next_wf == "A") {
                sum += x + m + a + s;
                // // cout  << " " << x + m + a + s << endl;
            }
        }

        // cout  << sum << endl;

        return sum;
    }

    struct ratings_range {
        pair<int64_t, int64_t> x;
        pair<int64_t, int64_t> m;
        pair<int64_t, int64_t> a;
        pair<int64_t, int64_t> s;
    };

    int part2solution() override {
        string line;

        map<string, vector<rule>> workflows;

        while (getline(inputFile, line)) {
            if (line == "") break;

            auto workflow_parts = tokenize(line, ' ');

            string name = workflow_parts[0];

            workflows[name] = vector<rule>();

            auto new_rules = tokenize(workflow_parts[1], ',');

            for (int i = 0; i < new_rules.size(); i++) {
                string new_rule_str = new_rules[i];

                rule new_rule;
                if (i == new_rules.size() - 1) {
                    new_rule.next = new_rule_str;
                } else {
                    new_rule.cat = new_rule_str[0];

                    new_rule.greater_than = new_rule_str[1] == '>' ? true : false;

                    auto found = new_rule_str.find(':', 0);
                    new_rule.number = stoi(string(new_rule_str.begin() + 2, new_rule_str.begin() + found));

                    new_rule.next = string(new_rule_str.begin() + found + 1, new_rule_str.end());
                }

                // // cout  << new_rule.cat << " " << new_rule.greater_than << " " << new_rule.number << " " <<
                // new_rule.next
                //      << endl;

                workflows[name].push_back(new_rule);
            }
            // // cout  << endl;
        }

        stack<pair<string, ratings_range>> ranges;

        ranges.push({"in", {{1, 4000}, {1, 4000}, {1, 4000}, {1, 4000}}});

        int64_t sum = 0;

        while (!ranges.empty()) {
            string next_wf = move(ranges.top().first);
            ratings_range rr = move(ranges.top().second);
            ranges.pop();

            if (next_wf == "A") {
                // cout  << next_wf << " : {" << rr.x.first << ", " << rr.x.second << "}, {" << rr.m.first << ", "
                //     << rr.m.second << "}, { " << rr.a.first << ", " << rr.a.second << "}, {" << rr.s.first << ", "
                //     << rr.s.second << "}";
//
                int64_t add = (rr.x.second - rr.x.first + 1) * (rr.m.second - rr.m.first + 1) *
                              (rr.a.second - rr.a.first + 1) * (rr.s.second - rr.s.first + 1);

                // cout  << "  => " << add << endl;

                sum += add;

                continue;
            } else if (next_wf == "R") {
                continue;
            };

            vector<rule> wf_rules = workflows[next_wf];

            for (int i = 0; i < wf_rules.size(); i++) {
                rule r = wf_rules[i];
                // // cout  << i << " " << r.cat << " " << r.number << " : " << r.next << "  GT: " << boolalpha
                //      << r.greater_than << endl;

                if (i == wf_rules.size() - 1) {
                    ranges.push({r.next, rr});
                    break;
                }
                auto range = r.cat == 'x' ? rr.x : r.cat == 'm' ? rr.m : r.cat == 'a' ? rr.a : rr.s;

                // // cout  << range.first << "--" << range.second << endl;

                if (r.greater_than) {
                    // Entire range above
                    if (range.first > r.number) {
                        ranges.push({r.next, rr});
                        break;
                    } else if (range.second < r.number) {
                        continue;
                    } else {
                        // above to the next workflow
                        // below to the next rule
                        if (r.cat == 'x') {
                            ranges.push({r.next, {{r.number + 1, rr.x.second}, rr.m, rr.a, rr.s}});
                            rr.x.second = r.number;
                        } else if (r.cat == 'm') {
                            ranges.push({r.next, {rr.x, {r.number + 1, rr.m.second}, rr.a, rr.s}});
                            rr.m.second = r.number;
                        } else if (r.cat == 'a') {
                            ranges.push({r.next, {rr.x, rr.m, {r.number + 1, rr.a.second}, rr.s}});
                            rr.a.second = r.number;
                        } else {
                            ranges.push({r.next, {rr.x, rr.m, rr.a, {r.number + 1, rr.s.second}}});
                            rr.s.second = r.number;
                        }
                        continue;
                    }
                } else {  // less than
                    if (range.second < r.number) {
                        ranges.push({r.next, rr});
                        break;
                    } else if (range.first > r.number) {
                        continue;
                    } else {
                        // above to the next workflow
                        // below to the next rule
                        if (r.cat == 'x') {
                            ranges.push({r.next, {{rr.x.first, r.number- 1}, rr.m, rr.a, rr.s}});
                            rr.x.first = r.number;
                        } else if (r.cat == 'm') {
                            ranges.push({r.next, {rr.x, {rr.m.first, r.number- 1}, rr.a, rr.s}});
                            rr.m.first = r.number;
                        } else if (r.cat == 'a') {
                            ranges.push({r.next, {rr.x, rr.m, {rr.a.first, r.number- 1}, rr.s}});
                            rr.a.first = r.number;
                        } else {
                            ranges.push({r.next, {rr.x, rr.m, rr.a, {rr.s.first, r.number- 1}}});
                            rr.s.first = r.number;
                        }
                        continue;
                    }
                }
            }
        }

        // cout  << sum << endl;
        return -1;
    }
};