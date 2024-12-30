#pragma once
#include "utils.h"

class Day {
   public:
    enum runType {
        example,
        input,
    };

    Day() {}
    ~Day() {
        inputFile.close();
    }

    void part1() {
        solutionSetup(); 

        int64_t answer = part1solution();
        cout << "Part 1: " << answer << endl;
    }

    void part2() {
        solutionSetup();
        
        int64_t answer = part2solution();
        cout << "Part 2: " << answer << endl;
    }

   protected:
    virtual int part1solution() = 0;
    virtual int part2solution() = 0;

    void solutionSetup() {
        inputFile.clear();
        inputFile.seekg(0);
    }

    ifstream inputFile;
};

#include "days.h"

class DayFactory
{
public:
    static Day *createDay(int day, Day::runType type) {
        switch (day) {
            case 1:
                return new Day_01(type);
            case 2:
                return new Day_02(type);
            case 3:
                return new Day_03(type);
            case 4:
                return new Day_04(type);
            case 5:
                return new Day_05(type);
            case 6:
                return new Day_06(type);
            case 7:
                return new Day_07(type);
            case 8:
                return new Day_08(type);
            case 9:
                return new Day_09(type);
            case 10:
                return new Day_10(type);
            case 11:
                return new Day_11(type);
            case 12:
                return new Day_12(type);
            case 13:
                return new Day_13(type);
            case 14:
                return new Day_14(type);
            case 15:
                return new Day_15(type);
            case 16:
                return new Day_16(type);
            case 17:
                return new Day_17(type);
            case 18:
                return new Day_18(type);
            case 19:
                return new Day_19(type);
            case 20:
                return new Day_20(type);
            case 21:
                return new Day_21(type);
            case 22:
                return new Day_22(type);
            case 23:
                return new Day_23(type);
            case 24:
                return new Day_24(type);
            case 25:
                return new Day_25(type);
            default:
                return nullptr;
        }
    }

};