#pragma once
#include "../Day.h"
#include "../utils.h"

class Day_25 : public Day {
   public:
    Day_25() = default;

    Day_25(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_25/example.txt");
                break;

            case runType::input:
                inputFile.open("day_25/input.txt");
                break;
        }
    };

    int part1solution() override {
        string line;

        unordered_map<string, multiset<string>> nodes_unti;
        map<string, int> count_unti;

        int product = 1;

        srand(time(0));

        while (getline(inputFile, line)) {
            auto node_list = tokenize(line, ' ');
            string node = node_list[0];
            if (nodes_unti.count(node) == 0) {
                nodes_unti.insert({node, multiset<string>()});
                count_unti.insert({node, 1});
            }
            for (int i = 1; i < node_list.size(); i++) {
                nodes_unti.at(node).insert(node_list[i]);
                if (nodes_unti.count(node_list[i]) == 0) {
                    nodes_unti.insert({node_list[i], multiset<string>()});
                    count_unti.insert({node_list[i], 1});
                }
                nodes_unti.at(node_list[i]).insert(node);
            }
        }
        while (true) {
            unordered_map<string, multiset<string>> nodes = nodes_unti;
            map<string, int> count = count_unti;

            while (nodes.size() > 2) {
                // Select an edge randomly
                auto item = nodes.begin();
                advance(item, rand() % nodes.size());
                string start_node = item->first;

                auto it = nodes[start_node].begin();
                advance(it, rand() %  nodes[start_node].size());
                string end_node = *it;

                // cout  << start_node << " --> " << end_node<< " : " << nodes.size() << endl;

                // Combine the vertecies connecting them
                // end_node into start_node
                nodes[start_node].erase(end_node);
                nodes[end_node].erase(start_node);

                for (auto it = nodes[end_node].begin(); it != nodes[end_node].end(); it++) {
                    // // cout  << "   " << *it << endl;
                    nodes[start_node].insert(*it);
                    nodes[*it].insert(start_node);
                    nodes[*it].erase(end_node);
                    /* code */
                }

                count[start_node] += count[end_node];

                nodes.erase(end_node);
                count.erase(end_node);
            }

            int cut_size = nodes.begin()->second.size();

            // // cout  << endl << "cut size : " << cut_size << endl;

            if (cut_size == 3) {
                for (auto it = count.begin(); it != count.end(); it++) {
                    // cout  << it->first << ": " << it->second << endl;
                    product *= it->second;
                }

                for (auto it = nodes.begin(); it != nodes.end(); it++) {
                    // cout  << it->first << ": " << it->second.size() << endl;
                }

                break;
            }
        }

        return product;
    }

    int part2solution() override {
        // Copy part 1 Here --

        return -1;
    }
};