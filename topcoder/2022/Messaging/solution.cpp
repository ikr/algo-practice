#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

vector<string> split(const string &s) {
    const auto i = s.find(' ');
    const auto j = s.find(' ', i + 1);
    return {s.substr(0, i), s.substr(i + 1, j - i - 1), s.substr(j + 1)};
}

struct Messaging final {
    string getNext(const vector<string> &ms, const int T) const {
        vector<priority_queue<pair<int, string>>> qs(T + 1);

        for (const auto &m : ms) {
            const auto parts = split(m);
            const auto text = parts[0];
            const auto prio = stoi(parts[1]);
            const auto time = stoi(parts[2]);

            if (time <= T) {
                qs[time].emplace(prio, text);
            }
        }

        for (int i = 0; i < sz(qs) - 1; ++i) {
            if (!qs[i].empty()) {
                qs[i].pop();
                continue;
            }

            for (int j = 0; j <= i; ++j) {
                if (!qs[j].empty()) {
                    qs[j].pop();
                    break;
                }
            }
        }

        if (!qs.back().empty()) return qs.back().top().second;

        for (int i = 0; i < sz(qs); ++i) {
            if (!qs[i].empty()) {
                return qs[i].top().second;
            }
        }

        return "";
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = Messaging{}.getNext({{"hello 1 1"},{"how 4 1"},{"are 2 3"},{"you 5 4"}}, 1);
        const string expected{"how"};
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = Messaging{}.getNext({{"hello 1 1"},{"how 4 1"},{"are 2 3"},{"you 5 4"}}, 2);
        const string expected{"hello"};
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = Messaging{}.getNext({"priority 9 1", "be 3 1", "queues 5 2", "can 4 3", "implemented 1 3", "but 8 7", "in 11 7", "would 2 7", "nlogn 12 8", "yours 21 10", "that 10 10", "slower 18 10", "than 14 11", "can 75 11", "be 50 11", "much 42 13", "be 30 30"}, 14);
        const string expected{"slower"};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
