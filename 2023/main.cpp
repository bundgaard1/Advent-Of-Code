#include "Day.h"
#include "utils.h"
using namespace std;

int run_day(int day_number) {
    Day *day = DayFactory::createDay(day_number, Day::runType::input);
    day->part1();
    day->part2();
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        cout << "Running day " << argv[1] << endl;
        int day = atoi(argv[1]);
        if (0 < day && day <= 25){
            run_day(day);
        } else {
            cout << "No such day: " << argv[1] << endl;
        }
    } else {
        cout << "Usage: *.exe"  << " [day_number]" << endl;
    } 

    return 0;
}
