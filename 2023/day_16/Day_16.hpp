#pragma once
#include "../Day.h"
#include "../utils.h"

class Day_16 : public Day {
   public:
    Day_16() = default;

    Day_16(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_16/example.txt");
                break;

            case runType::input:
                inputFile.open("day_16/input.txt");
                break;
        }
    };

    enum heading {
        up,
        down,
        left,
        right,
    };

    struct light {
        int64_t x;
        int64_t y;
        heading head;
        light(int64_t _x, int64_t _y, heading _h) : x(_x), y(_y), head(_h) {}

        light next_pos() {
            switch (head) {
                case heading::up:
                    return light(x, y - 1, head);
                    break;
                case heading::down:
                    return light(x, y + 1, head);
                    break;
                case heading::left:
                    return light(x - 1, y, head);
                    break;
                case heading::right:
                    return light(x + 1, y, head);
                    break;
                default:
                    break;
            }
            return light(x, y, head);
        }
        bool is_valid(int height, int width) { return (0 <= x && x < width) && (0 <= y && y < height); }

        bool operator<(const light& rhs) const {
            return ((x << 16) + (y << 8) + head) < ((rhs.x << 16) + (rhs.y << 8) + rhs.head);
        }
    };

    int part1solution() override {
        string line;

        vector<string> layout;

        while (getline(inputFile, line)) {
            layout.push_back(line);
        }

        int layout_height = layout.size();
        int layout_width = layout[0].length();

        vector<string> energized(layout.size(), string(layout[0].length(), '.'));

        // Set up
        set<light> closed;
        stack<light> open;
        open.push(light(-1, 0, heading::right));

        while (!open.empty()) {
            light curr = open.top();
            // // // cout   << curr.x << ", " << curr.y << " heading " << curr.head << "  : ";

            if (closed.count(curr)) {
                // // // cout   << "already visited" << endl;
                open.pop();
                continue;
            }
            closed.insert(curr);
            if (curr.is_valid(layout_height, layout_width)) {
                energized[curr.y][curr.x] = '#';
            }

            light next = curr.next_pos();
            open.pop();
            if (!next.is_valid(layout_height, layout_width)) {
                // // // cout   << "next is invalid " << endl;
                continue;
            }

            char next_char = layout[next.y][next.x];
            // // // cout   << next_char << endl;
            switch (next_char) {
                case '.':
                    open.push(next);
                    break;
                case '/':
                    if (next.head == heading::up)
                        open.push(light(next.x, next.y, heading::right));
                    else if (next.head == heading::right)
                        open.push(light(next.x, next.y, heading::up));
                    else if (next.head == heading::down)
                        open.push(light(next.x, next.y, heading::left));
                    else if (next.head == heading::left)
                        open.push(light(next.x, next.y, heading::down));
                    break;
                case '\\':
                    if (next.head == heading::up)
                        open.push(light(next.x, next.y, heading::left));
                    else if (next.head == heading::right)
                        open.push(light(next.x, next.y, heading::down));
                    else if (next.head == heading::down)
                        open.push(light(next.x, next.y, heading::right));
                    else if (next.head == heading::left)
                        open.push(light(next.x, next.y, heading::up));
                    break;
                case '|':
                    if (next.head == heading::up || next.head == heading::down)
                        open.push(light(next.x, next.y, next.head));
                    else if (next.head == heading::right || next.head == heading::left) {
                        open.push(light(next.x, next.y, heading::down));
                        open.push(light(next.x, next.y, heading::up));
                    }
                    break;
                case '-':
                    if (next.head == heading::right || next.head == heading::left)
                        open.push(light(next.x, next.y, next.head));
                    else if (next.head == heading::up || next.head == heading::down) {
                        open.push(light(next.x, next.y, heading::left));
                        open.push(light(next.x, next.y, heading::right));
                    }
                    break;
                default:
                    break;
            }
        }

        // for (auto a : layout) {
        //     // // cout   << a << endl;
        // }
        // // // cout   << endl;

        // for (auto s : energized) {
        //     // // cout   << s << endl;
        // }
        int count = 0;
        for (int i = 0; i < layout_width; i++) {
            for (int j = 0; j < layout_width; j++) {
                if (energized[i][j] == '#') {
                    count++;
                }
            }
        }

        return count;
    }

    int part2solution() override {
        string line;

        vector<string> layout;

        while (getline(inputFile, line)) {
            layout.push_back(line);
        }

        int layout_height = layout.size();
        int layout_width = layout[0].length();

        vector<light> starting_points;

        // from above
        for (int i = 0; i < layout_width; i++) {
            starting_points.push_back(light(i, -1, heading::down));
            starting_points.push_back(light(i, layout_height, heading::up));
        }
        for (int i = 0; i < layout_height; i++) {
            starting_points.push_back(light(-1, i, heading::right));
            starting_points.push_back(light(layout_width, i, heading::left));
        }

        int max_count = 0;

        for (light start : starting_points) {
            vector<string> energized(layout.size(), string(layout[0].length(), '.'));

            // Set up
            set<light> closed;
            stack<light> open;
            open.push(start);

            while (!open.empty()) {
                light curr = open.top();
                // // // cout   << curr.x << ", " << curr.y << " heading " << curr.head << "  : ";

                if (closed.count(curr)) {
                    // // // cout   << "already visited" << endl;
                    open.pop();
                    continue;
                }
                closed.insert(curr);
                if (curr.is_valid(layout_height, layout_width)) {
                    energized[curr.y][curr.x] = '#';
                }

                light next = curr.next_pos();
                open.pop();
                if (!next.is_valid(layout_height, layout_width)) {
                    // // // cout   << "next is invalid " << endl;
                    continue;
                }

                char next_char = layout[next.y][next.x];
                // // // cout   << next_char << endl;
                switch (next_char) {
                    case '.':
                        open.push(next);
                        break;
                    case '/':
                        if (next.head == heading::up)
                            open.push(light(next.x, next.y, heading::right));
                        else if (next.head == heading::right)
                            open.push(light(next.x, next.y, heading::up));
                        else if (next.head == heading::down)
                            open.push(light(next.x, next.y, heading::left));
                        else if (next.head == heading::left)
                            open.push(light(next.x, next.y, heading::down));
                        break;
                    case '\\':
                        if (next.head == heading::up)
                            open.push(light(next.x, next.y, heading::left));
                        else if (next.head == heading::right)
                            open.push(light(next.x, next.y, heading::down));
                        else if (next.head == heading::down)
                            open.push(light(next.x, next.y, heading::right));
                        else if (next.head == heading::left)
                            open.push(light(next.x, next.y, heading::up));
                        break;
                    case '|':
                        if (next.head == heading::up || next.head == heading::down)
                            open.push(light(next.x, next.y, next.head));
                        else if (next.head == heading::right || next.head == heading::left) {
                            open.push(light(next.x, next.y, heading::down));
                            open.push(light(next.x, next.y, heading::up));
                        }
                        break;
                    case '-':
                        if (next.head == heading::right || next.head == heading::left)
                            open.push(light(next.x, next.y, next.head));
                        else if (next.head == heading::up || next.head == heading::down) {
                            open.push(light(next.x, next.y, heading::left));
                            open.push(light(next.x, next.y, heading::right));
                        }
                        break;
                    default:
                        break;
                }
            }

            // for (auto a : layout) {
            //     // // cout   << a << endl;
            // }
            // // // cout   << endl;

            // for (auto s : energized) {
            //     // // cout   << s << endl;
            // }
            int count = 0;
            for (int i = 0; i < layout_width; i++) {
                for (int j = 0; j < layout_width; j++) {
                    if (energized[i][j] == '#') {
                        count++;
                    }
                }
            }

            max_count = max(max_count, count);
        }
        return max_count;
    }
};