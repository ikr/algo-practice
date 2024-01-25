#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

struct AdventCalendar final {
    vector<string> eat(vector<string> rows) const {
        set<int> av;
        for (const auto &row : rows) {
            const auto tokens = split(" ", row);
            for (const auto &token : tokens) {
                if (token.empty() || token[0] == 'X') continue;
                av.insert(stoi(token));
            }
        }

        const auto to_open = [&]() -> int {
            for (int i = 1; i < 25; ++i) {
                if (av.count(i)) return i;
            }
            return -1;
        }();

        for (auto &row : rows) {
            {
                const auto needle = " " + to_string(to_open) + " ";
                const auto i = row.find(needle);
                if (i != string::npos) {
                    row[i + 1] = 'X';
                    if (to_open > 9) row[i + 2] = 'X';
                    break;
                }
            }
            {
                const auto needle = to_string(to_open) + " ";
                const auto i = row.find(needle);
                if (i == 0U) {
                    row[i] = 'X';
                    if (to_open > 9) row[i + 1] = 'X';
                    break;
                }
            }
            {
                const auto needle = " " + to_string(to_open);
                const auto i = row.find(needle);
                if (i == row.size() - needle.size()) {
                    row[i + 1] = 'X';
                    if (to_open > 9) row[i + 2] = 'X';
                    break;
                }
            }
        }

        return rows;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = AdventCalendar{}.eat({"19 9 2 24 10 ", " 1 18 7 3 11", " 20 21 4 17 16 23", " 14 12 6 5 ", " 8 22 13 15"});
        const vector<string> expected{"19 9 2 24 10 ", " X 18 7 3 11", " 20 21 4 17 16 23", " 14 12 6 5 ", " 8 22 13 15" };
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = AdventCalendar{}.eat({"19 9 X 24 10 ", " X 18 7 3 11", " 20 21 4 17 16 23", " 14 12 6 5 ", " 8 22 13 15"});
        const vector<string> expected{"19 9 X 24 10 ", " X 18 7 X 11", " 20 21 4 17 16 23", " 14 12 6 5 ", " 8 22 13 15" };
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
