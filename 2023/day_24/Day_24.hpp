#pragma once
#include "../Day.h"
#include "../utils.h"


class Day_24 : public Day {
   public:
    Day_24() = default;

    double upper;
    double lower;

    Day_24(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_24/example.txt");
                upper = 27;                
                lower = 7; 
                break;
            case runType::input:
                inputFile.open("day_24/input.txt");
                upper = 400000000000000;
                lower = 200000000000000; 
                break;
        }
    };

    struct vec2 {
        double x, y;

        vec2() : x(0), y(0) {}
        vec2(double _x, double _y) : x(_x), y(_y) {}

        bool is_parralel(vec2& other) {
            double a = x * other.y - y * other.x;
            return a == 0;
        }

        vec2 sub(vec2& other) { return vec2(x - other.x, y - other.y); }

        vec2 neg() { return vec2(-x, -y); }
    };

    struct mat22 {
        double x1, y1, x2, y2;

        mat22(double a) : x1(a), x2(a), y1(a), y2(a) {}

        mat22(vec2 a, vec2 b) {
            x1 = a.x;
            y1 = a.y;
            x2 = b.x;
            y2 = b.y;
        }

        // the mat22 is inverable;
        mat22 inv() {
            mat22 i = mat22(0);
            double r = x1 * y2 - x2 * y1;
            i.x1 = y2 / r;
            i.y1 = -y1 / r;
            i.x2 = -x2 / r;
            i.y2 = x1 / r;
            return i;
        }
        vec2 mult(vec2& other) { return vec2(x1 * other.x + x2 * other.y, y1 * other.x + y2 * other.y); }
    };

    vec2 solve(mat22 A, vec2 b) { return A.inv().mult(b); }

    int part1solution() override {
        string line;

        vector<tuple<double, double, double>> position;
        vector<tuple<double, double, double>> velocity;

        while (getline(inputFile, line)) {
            auto pos_vel = tokenize(line, '@');

            auto pos = tokenize(pos_vel[0], ',');
            auto vel = tokenize(pos_vel[1], ',');

            position.push_back(make_tuple(stod(pos[0]), stod(pos[1]), stod(pos[2])));
            velocity.push_back(make_tuple(stod(vel[0]), stod(vel[1]), stod(vel[2])));
        } 

        int total = 0;

        for (int i = 0; i < position.size(); i++) {
            for (int j = i+1; j < position.size(); j++) {
                // // cout  << i << " & " << j << endl;

                auto pos1 = position[i];
                auto vel1 = velocity[i];

                auto pos2 = position[j];
                auto vel2 = velocity[j];

                vec2 a1 = vec2(get<0>(pos1), get<1>(pos1));
                vec2 a2 = vec2(get<0>(pos2), get<1>(pos2));

                vec2 v1 = vec2(get<0>(vel1), get<1>(vel1));
                vec2 v2 = vec2(get<0>(vel2), get<1>(vel2));
                
                if(v1.is_parralel(v2)){
                    // // cout  << "Velocities is parrallel" << endl << endl;
                    continue;
                }

                vec2 t = solve(mat22(v1.neg(), v2), vec2(a1.x - a2.x, a1.y - a2.y));

                // // cout  << "Hits at: " << t.x << " & " << t.y << endl;
                 
                if(!(t.x >= 0 && t.y >= 0)){
                    // // cout  << "Hit in past " << endl <<  endl;
                    continue;
                }

                vec2 intsec = vec2(a1.x + t.x * v1.x, a1.y + t.x * v1.y);

                // // cout  << "Intersection at : " << intsec.x << ',' << intsec.y << endl;

                if(lower <= intsec.x && intsec.x <= upper && lower <= intsec.y && intsec.y <= upper){
                    total++;
                    // // cout  << "Within bounds" << endl << endl;
                } else {
                    // // cout  << "outside bounds" << endl << endl;
                }
            }
        }

        return total;
    }

    int part2solution() override {
        // Copy part 1 Here --

        return -1;
    }
};