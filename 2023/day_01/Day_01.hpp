#include "../Day.h"
#include "../utils.h"

class Day_01 : public Day {
   public:
    Day_01() = default;

    Day_01(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_01/example2.txt");
                break;

            case runType::input:
                inputFile.open("day_01/input.txt");
                break;
        }
    };

    int part1solution() override {
        string line;

        int sum = 0;

    	while (getline(inputFile, line)) {
            vector<int> curr;
            for (size_t i = 0; i < line.size(); i++) {
                char c = line[i];
                if (isdigit(c)) {
                    curr.push_back(c - '0');
                }
            }
             //cout << curr.size();

            sum += curr[0] * 10 + curr[curr.size() - 1];
        }

        return sum;
    }

    int part2solution() override {
        vector<string> digits{{"zero"}, {"one"}, {"two"}, {"three"}, {"four"},
                                         {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

        string line;

        int sum = 0;

        while (getline(inputFile, line)) {
            vector<int> curr;
            for (size_t i = 0; i < line.size(); i++) {
                char c = line[i];
                if (isdigit(c)) {
                    curr.push_back(c - '0');
                } else {
                    for (int j = 1; j <= 10; j++)
                    {
                        if(digits[j].size() + i > line.size()){
                            continue;
                        } else {
                            string sub = line.substr(i,digits[j].size());
                            if(sub == digits[j]){
                                curr.push_back(j);
                            }
                        }
                    }
                    
                }
            }

            // print_vector(curr);

            sum += curr[0] * 10 + curr[curr.size() - 1];
        }

        return sum;
    }
};