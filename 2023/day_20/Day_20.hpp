#pragma once
#include "../Day.h"
#include "../utils.h"

class Day_20 : public Day {
   public:
    Day_20() = default;

    Day_20(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_20/example.txt");
                break;

            case runType::input:
                inputFile.open("day_20/input.txt");
                break;
        }
    };

    enum mod_type {
        FF,
        Con,
        BC,
    };

    struct Module {
        mod_type type;
        string name;
        vector<string> output;
        bool state = false;  // For the FF
        map<string, bool> input;
    };

    int part1solution() override {
        string line;

        map<string, Module> modules;

        while (getline(inputFile, line)) {
            auto tokens = tokenize(line, '>');
            Module new_module;
            if (tokens[0] == "broadcaster") {
                new_module.name = tokens[0];
                new_module.type = mod_type::BC;
            } else {
                new_module.name = tokens[0].substr(1);
                new_module.type = tokens[0][0] == '%' ? mod_type::FF : mod_type::Con;
            }
            auto out = tokenize(tokens[1], ',');

            for (auto m : out) {
                new_module.output.push_back(m);
            }

            modules[new_module.name] = new_module;
        }

        for (auto m : modules) {
            for (auto o : m.second.output) {
                modules[o].input[m.first] = false;
            }
        }

        // for (auto m : modules) {
        //     // cout  << m.second.name << ":  " << m.second.type << endl;

        //     // cout  << "   INPUT:  ";
        //     for (auto in : m.second.input) {
        //         // cout  << in.first << ", ";
        //     }
        //     // cout  << endl << "   OUTPUT:  ";
        //     for (auto out : m.second.output) {
        //         // cout  << out << ", ";
        //     }
        //     // cout  << endl;
        // }

        int64_t lows = 0;
        int64_t highs = 0;

        // Simulate the
        for (int i = 1; i <= 10000; i++) {
            // // cout  << endl << "BUTTON PUSh: " << i << endl;
            queue<tuple<string, bool, string>> pulses;
            pulses.push({"button", false, "broadcaster"});

            while (!pulses.empty()) {
                string from = get<0>(pulses.front());
                bool pulse = get<1>(pulses.front());
                string dest = get<2>(pulses.front());
                pulses.pop();

                if (pulse) {
                    highs++;
                } else {
                    lows++;
                }

                Module& dest_mod = modules[dest];

                switch (dest_mod.type) {
                    case mod_type::FF:
                        if (pulse == false) {
                            dest_mod.state = !dest_mod.state;
                            for (auto out : dest_mod.output) {
                                pulses.push({dest, dest_mod.state, out});
                                // // cout  << dest << "-" << dest_mod.state << "->" << out << endl;
                            }
                        }
                        break;
                    case mod_type::Con:
                        dest_mod.input[from] = pulse;
                        {
                            bool send_pulse = false;

                            for (auto p : dest_mod.input) {
                                // // cout  << p.first << ": " << p.second << endl;
                                if (!p.second) {
                                    send_pulse = true;
                                    break;
                                }
                            }

                            for (auto out : dest_mod.output) {
                                pulses.push({dest, send_pulse, out});
                                // // cout  << dest << "-" << send_pulse << "->" << out << endl;
                            }
                        }
                        break;
                    case mod_type::BC:
                        for (auto out : dest_mod.output) {
                            pulses.push({dest, pulse, out});
                            // // cout  << dest << " -" << pulse << "-> " << out << endl;
                        }
                        break;
                    default:
                        break;
                }
            }

            // // cout  << endl;
        }
        // cout  << "Lows: " << lows << endl;
        // cout  << "Highs:" << highs << endl;

        
        // cout  << "Part 1 :" <<  lows * highs << endl;

        return -1;
    }

    int part2solution() override {
        string line;

        map<string, Module> modules;

        while (getline(inputFile, line)) {
            auto tokens = tokenize(line, '>');
            Module new_module;
            if (tokens[0] == "broadcaster") {
                new_module.name = tokens[0];
                new_module.type = mod_type::BC;
            } else {
                new_module.name = tokens[0].substr(1);
                new_module.type = tokens[0][0] == '%' ? mod_type::FF : mod_type::Con;
            }
            auto out = tokenize(tokens[1], ',');

            for (auto m : out) {
                new_module.output.push_back(m);
            }

            modules[new_module.name] = new_module;
        }

        for (auto m : modules) {
            for (auto o : m.second.output) {
                modules[o].input[m.first] = false;
            }
        }

        // for (auto m : modules) {
        //     // cout  << m.second.name << ":  " << m.second.type << endl;

        //     // cout  << "   INPUT:  ";
        //     for (auto in : m.second.input) {
        //         // cout  << in.first << ", ";
        //     }
        //     // cout  << endl << "   OUTPUT:  ";
        //     for (auto out : m.second.output) {
        //         // cout  << out << ", ";
        //     }
        //     // cout  << endl;
        // }

        int64_t lows = 0;
        int64_t highs = 0;

        int n = 0;
        vector<int64_t> zr_in_periods;

        // Simulate the
        for (int i = 1; i <= 10000; i++) {
            // // cout  << endl << "BUTTON PUSh: " << i << endl;
            queue<tuple<string, bool, string>> pulses;
            pulses.push({"button", false, "broadcaster"});

            while (!pulses.empty()) {
                string from = get<0>(pulses.front());
                bool pulse = get<1>(pulses.front());
                string dest = get<2>(pulses.front());
                pulses.pop();

                if (dest == "zr" && pulse) {
                    //// cout  << from << ": " << i << endl;
                    zr_in_periods.push_back(i);
                    n++;
                }

                if (pulse) {
                    highs++;
                } else {
                    lows++;
                }

                Module& dest_mod = modules[dest];

                switch (dest_mod.type) {
                    case mod_type::FF:
                        if (pulse == false) {
                            dest_mod.state = !dest_mod.state;
                            for (auto out : dest_mod.output) {
                                pulses.push({dest, dest_mod.state, out});
                                // // cout  << dest << "-" << dest_mod.state << "->" << out << endl;
                            }
                        }
                        break;
                    case mod_type::Con:
                        dest_mod.input[from] = pulse;
                        {
                            bool send_pulse = false;

                            for (auto p : dest_mod.input) {
                                // // cout  << p.first << ": " << p.second << endl;
                                if (!p.second) {
                                    send_pulse = true;
                                    break;
                                }
                            }

                            for (auto out : dest_mod.output) {
                                pulses.push({dest, send_pulse, out});
                                // // cout  << dest << "-" << send_pulse << "->" << out << endl;
                            }
                        }
                        break;
                    case mod_type::BC:
                        for (auto out : dest_mod.output) {
                            pulses.push({dest, pulse, out});
                            // // cout  << dest << " -" << pulse << "-> " << out << endl;
                        }
                        break;
                    default:
                        break;
                }
            }

            if(n >= 4){
                break;
            }

            // // cout  << endl;
        }
        int64_t button_presses = 1;

        for (auto a : zr_in_periods)
        {
            button_presses = lcm(a, button_presses);
        }
        


        // cout  << "Part 2: "<< button_presses << endl;
        

        return -1;
    }
};