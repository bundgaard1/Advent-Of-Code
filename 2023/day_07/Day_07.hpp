#pragma once
#include "../Day.h"
#include "../utils.h"

class Day_07 : public Day {
   public:
    Day_07() = default;

    Day_07(Day::runType r) {
        switch (r) {
            case runType::example:
                inputFile.open("day_07/example.txt");
                break;

            case runType::input:
                inputFile.open("day_07/input.txt");
                break;
        }
    };

    enum Type {
        high_card,
        one_pair,
        two_pairs,
        three_oak,
        full_house,
        four_oak,
        five_oak,
    };

    static const int N = 5;

    enum card {
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        T,
        J,
        Q,
        K,
        A,
    };

    struct Hand {
        vector<card> cards;
        Type hand_type;
        int bid;

        bool operator<(const Hand& a) const {
            if (hand_type != a.hand_type) return hand_type < a.hand_type;

            for (size_t i = 0; i < N; i++) {
                if (cards[i] != a.cards[i]) return cards[i] < a.cards[i];
            }
            return true;
        }

        void determine_type() {
            if (is_5oak())
                hand_type = Type::five_oak;
            else if (is_4oak())
                hand_type = Type::four_oak;
            else if (is_fh())
                hand_type = Type::full_house;
            else if (is_3oak())
                hand_type = Type::three_oak;
            else if (is_2pair())
                hand_type = Type::two_pairs;
            else if (is_pair())
                hand_type = Type::one_pair;
            else
                hand_type = Type::high_card;
            return;
        }

        int count_occur(card c) {
            int count = 0;
            for (size_t i = 0; i < N; i++) {
                if (c == cards[i]) count++;
            }
            return count;
        }

        bool is_5oak() { return count_occur(cards[0]) == 5; }

        bool is_4oak() { return count_occur(cards[0]) == 4 || count_occur(cards[1]) == 4; }
        bool is_fh() {
            set<int> counts;
            for (int c = 0; c < N; c++) {
                int count = 0;
                for (size_t i = 0; i < N; i++) {
                    if (cards[c] == cards[i]) count++;
                }
                counts.insert(count);
            }

            return (counts.count(3) && counts.count(2));
        }
        bool is_3oak() {
            int max_count = 0;
            for (int c = 0; c < N; c++) {
                int count = 0;
                for (size_t i = 0; i < N; i++) {
                    if (cards[c] == cards[i]) count++;
                }
                max_count = max(max_count, count);
            }

            return max_count == 3;
        }
        bool is_2pair() {
            int num_pairs = 0;
            for (int c = 0; c < N; c++) {
                int count = count_occur(cards[c]);
                if (count == 2) num_pairs++;
            }

            return num_pairs == 4;
        }

        bool is_pair() {
            int num_pairs = 0;
            for (int c = 0; c < N; c++) {
                int count = count_occur(cards[c]);
                if (count == 2) num_pairs++;
            }
            return num_pairs == 2;
        }
    };

    card char_to_card(char c) {
        switch (c) {
            case '2':
                return card::two;
            case '3':
                return card::three;
            case '4':
                return card::four;
            case '5':
                return card::five;
            case '6':
                return card::six;
            case '7':
                return card::seven;
            case '8':
                return card::eight;
            case '9':
                return card::nine;
            case 'T':
                return card::T;
            case 'J':
                return card::J;
            case 'Q':
                return card::Q;
            case 'K':
                return card::K;
            case 'A':
                return card::A;

            default:
                assert(0 && "MISTAKE AT CHARACTER->CARD convertion");
        };
        return card::A;
    }

    int part1solution() override {
        string line;
        vector<Hand> hands;

        while (getline(inputFile, line)) {
            auto tokens = tokenize(line, ' ');
            Hand h;
            for (size_t i = 0; i < tokens[0].size(); i++) {
                h.cards.push_back(char_to_card(tokens[0][i]));
            }

            h.bid = stoi(tokens[1]);
            h.determine_type();

            hands.push_back(h);
        }
        /*
        for (auto h : hands) {
            print_vector(h.cards);
            // cout  << " " << h.bid << " Type: " << h.hand_type << endl;
        }
        */

        sort(hands.begin(), hands.end());
        // cout  << "===sorted===" << endl;

        i64 total_winnings = 0;

        int rank = 1;
        for (auto h : hands) {
            // cout  << rank << " : ";
            print_vector(h.cards);
            // cout  << " Type: " << h.hand_type << endl;
            total_winnings += rank * h.bid;
            rank++;
        }

        return total_winnings;
    }

    enum card2 {
        J2,
        two2,
        three2,
        four2,
        five2,
        six2,
        seven2,
        eight2,
        nine2,
        T2,
        Q2,
        K2,
        A2,
    };

    struct Hand2 {
        vector<card2> cards;
        Type hand_type;
        int bid;

        bool operator<(const Hand2& a) const {
            if (hand_type != a.hand_type) return hand_type < a.hand_type;

            for (size_t i = 0; i < N; i++) {
                if (cards[i] != a.cards[i]) return cards[i] < a.cards[i];
            }
            return true;
        }

        void determine_type2() {
            if (is_5oak2())
                hand_type = Type::five_oak;
            else if (is_4oak2())
                hand_type = Type::four_oak;
            else if (is_fh2())
                hand_type = Type::full_house;
            else if (is_3oak2())
                hand_type = Type::three_oak;
            else if (is_2pair2())
                hand_type = Type::two_pairs;
            else if (is_pair2())
                hand_type = Type::one_pair;
            else
                hand_type = Type::high_card;
            return;
        }

        int count_occur2(card2 c) {
            int count = 0;
            for (size_t i = 0; i < N; i++) {
                if (c == cards[i] || cards[i] == card2::J2) count++;
            }
            return count;
        }

        bool is_5oak2() {
            for (int i = 0; i < 5; i++) {
                if (count_occur2(cards[i]) == 5) return true;
            }

            return false;
        }

        bool is_4oak2() {
            for (int i = 0; i < 5; i++) {
                if (count_occur2(cards[i]) == 4) return true;
            }

            return false;
        }
        bool is_fh2() {
            set<int> counts;
            int j_count = count_occur2(card2::J2);
            for (int i = 0; i < N; i++) {
                counts.insert(count_occur2(cards[i]));
            }

            if (counts.count(3) && counts.count(2) && !j_count) return true;

            if (counts.count(3) && !counts.count(2) && j_count == 1) return true;

            return false;

        }
        bool is_3oak2() {
            for (int i = 0; i < 5; i++) {
                if (count_occur2(cards[i]) == 3) return true;
            }

            return false;
        }
        bool is_2pair2() {
            int num_pairs = 0;
            set<card2> card_set;
            int j_count = count_occur2(card2::J2);
            for (int i = 0; i < N; i++) {
                card_set.insert(cards[i]);
                int count = count_occur2(cards[i]);
                if (count_occur2(cards[i]) == 2) num_pairs++;
            }

            return (j_count && card_set.size() == 4) || (!j_count && num_pairs == 4);
        }

        bool is_pair2() {
            for (int i = 0; i < 5; i++) {
                if (count_occur2(cards[i]) == 2) return true;
            }

            return false;
        }
    };

    card2 char_to_card2(char c) {
        switch (c) {
            case '2':
                return card2::two2;
            case '3':
                return card2::three2;
            case '4':
                return card2::four2;
            case '5':
                return card2::five2;
            case '6':
                return card2::six2;
            case '7':
                return card2::seven2;
            case '8':
                return card2::eight2;
            case '9':
                return card2::nine2;
            case 'T':
                return card2::T2;
            case 'J':
                return card2::J2;
            case 'Q':
                return card2::Q2;
            case 'K':
                return card2::K2;
            case 'A':
                return card2::A2;

            default:
                assert(0 && "MISTAKE AT CHARACTER->CARD convertion");
        };
        return card2::A2;
    }

    int part2solution() override {
        string line;
        vector<Hand2> hands;

        while (getline(inputFile, line)) {
            auto tokens = tokenize(line, ' ');
            Hand2 h;
            for (size_t i = 0; i < tokens[0].size(); i++) {
                h.cards.push_back(char_to_card2(tokens[0][i]));
            }

            h.bid = stoi(tokens[1]);
            h.determine_type2();

            hands.push_back(h);
        }

        for (auto h : hands) {
            print_vector(h.cards);
            // cout  << " " << h.bid << " Type: " << h.hand_type << endl;
        }

        sort(hands.begin(), hands.end());
        // cout  << "===sorted===" << endl;

        i64 total_winnings = 0;

        int rank = 1;
        for (auto h : hands) {
            // cout  << rank << " : ";
            print_vector(h.cards);
            // cout  << " Type: " << h.hand_type << endl;
            total_winnings += rank * h.bid;
            rank++;
        }

        return total_winnings;
    }
};