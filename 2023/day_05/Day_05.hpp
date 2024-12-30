#pragma once
#include "../Day.h"
#include "../utils.h"

typedef int64_t i64;

class Day_05 : public Day {
   public:
    Day_05() = default;

    Day_05(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_05/example.txt");
                break;

            case runType::input:
                inputFile.open("day_05/input.txt");
                break;
        }
    };

    struct map_interval {
        i64 start;
        i64 end;
        i64 offset;

        void print() { 
            //// cout  << "Interval: " << start << " -- " << end << "  :  " << offset << endl;
            return;
            }
    };

    i64 get_offset(vector<map_interval>& the_map, i64 source) {
        for (auto curr : the_map) {
            if (curr.start <= source && source < curr.end) {
                return curr.offset;
            }
        }

        return 0;
    }

    int part1solution() override {
        string line;

        vector<i64> seeds;

        vector<vector<map_interval>> almanac_maps(7);

        getline(inputFile, line);
        auto seeds_nums = tokenize(line, ' ');
        for (auto seed : seeds_nums) {
            seeds.push_back(stoull(seed));
        }
        getline(inputFile, line);

        int map_index = 0;

        while (getline(inputFile, line)) {
            if (line == "") {
                map_index++;
                // // cout  << "next map" << endl;
                continue;
            }

            auto tokens = tokenize(line, ' ');

            i64 dest_range_start = stoll(tokens[0]);
            i64 sorc_range_start = stoll(tokens[1]);
            i64 range_length = stoll(tokens[2]);

            map_interval new_interval;
            new_interval.start = sorc_range_start;
            new_interval.end = sorc_range_start + range_length;
            new_interval.offset = dest_range_start - sorc_range_start;

            // new_interval.print();

            almanac_maps.at(map_index).push_back(new_interval);
        }

        i64 min_loc = INT64_MAX;

        for (i64 seed : seeds) {
            i64 n = seed;
            // // cout  << seed;

            for (auto& curr_map : almanac_maps) {
                i64 offset = get_offset(curr_map, n);

                n += offset;
                // // cout  << " --> " << n;
            }

            min_loc = min(n, min_loc);

            // // cout  << endl;
        }

        return min_loc;
    }

    struct interval {
        i64 start;
        i64 end;
        interval(i64 _start, i64 _end) : start(_start), end(_end) {}
        interval() : start(0), end(0) {}
    };

    bool isOverlap(const interval& i1, const interval& i2) { return (i1.start < i2.end && i2.start < i1.end); }

    vector<interval> get_next_numbers(vector<map_interval>& the_map, interval source) {
        vector<interval> new_intervals;
        stack<interval> remaining_numbers;

        interval curr_interval;
        remaining_numbers.push(source);

        while (!remaining_numbers.empty()) {
            curr_interval = remaining_numbers.top();
            remaining_numbers.pop();

            // Find a fitting interval,
            for (auto i : the_map) {
                if (isOverlap(interval(i.start, i.end), curr_interval)) {
                    if(i.start <= curr_interval.start){
                        if(i.end < curr_interval.end){
                            new_intervals.push_back(interval(curr_interval.start + i.offset, i.end + i.offset));
                            remaining_numbers.push(interval(i.end, curr_interval.end));
                        } else {
                            new_intervals.push_back(interval(curr_interval.start + i.offset, curr_interval.end + i.offset));
                        }
                    } else {
                        remaining_numbers.push(interval(curr_interval.start, i.start));
                        if(curr_interval.end < i.end ){     
                            new_intervals.push_back(interval(i.start + i.offset, curr_interval.end + i.offset));
                        } else {
                            new_intervals.push_back(interval(i.start + i.offset, i.end + i.offset));
                            remaining_numbers.push(interval(i.end, curr_interval.end));
                        }
                    }

                    goto interval_found;
                }
            }

            goto not_found;

        interval_found:
            continue;

        not_found:
            new_intervals.push_back(curr_interval);
            continue;
        }

        return new_intervals;
    }

    int part2solution() override {
        string line;

        vector<interval> seeds;

        vector<vector<map_interval>> almanac_maps(7);

        getline(inputFile, line);
        auto seeds_nums = tokenize(line, ' ');
        for (int i = 0; i < seeds_nums.size(); i += 2) {
            i64 start = stoll(seeds_nums[i]);
            i64 end = stoll(seeds_nums[i]) + stoll(seeds_nums[i + 1]);
            interval new_interval;
            new_interval.start = start;
            new_interval.end = end;
            seeds.push_back(new_interval);
        }

        getline(inputFile, line);

        int map_index = 0;

        while (getline(inputFile, line)) {
            if (line == "") {
                map_index++;
                continue;
            }

            auto tokens = tokenize(line, ' ');

            i64 dest_range_start = stoll(tokens[0]);
            i64 sorc_range_start = stoll(tokens[1]);
            i64 range_length = stoll(tokens[2]);

            map_interval new_interval;
            new_interval.start = sorc_range_start;
            new_interval.end = sorc_range_start + range_length;
            new_interval.offset = dest_range_start - sorc_range_start;

            almanac_maps.at(map_index).push_back(new_interval);
        }

        vector<interval> numbers = seeds;

        // cout  << "Starting Seeds: " << endl;
        for (auto i : numbers) {
            // cout  << i.start << "-" << i.end << endl;
        }

        // cout  << "Maps: " << endl;
        for (auto m : almanac_maps) {
            
            for (auto i : m)
            {
                i.print();
            }
            // cout  << endl;
            
        }


        i64 min_loc = INT64_MAX;

        for (auto& curr_map : almanac_maps) {
            vector<interval> next_numbers;

            for (auto n : numbers) {
                vector<interval> new_numbers = get_next_numbers(curr_map, n);
                
                for (auto i : new_numbers)
                {
                    next_numbers.push_back(i);
                }
                
            }

            // cout  << "Numbers size:" << numbers.size() << endl;
            
            numbers.clear();

            for (auto i : next_numbers)
            {
                numbers.push_back(i);
            }
            
        }

        // cout  << "Ending Locations: " << endl;
        for (auto i : numbers) {
            // cout  << i.start << "-" << i.end << endl;
            min_loc = min(min_loc, i.start);
        }

        return min_loc;
    }
};