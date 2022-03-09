#include "lest.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
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

struct OptimalMemoryGame final {
    int findPairs(const string &xs) const {
        map<char, int> fs_m;
        for (const auto x : xs) ++fs_m[x];

        const int unkn = fs_m['-'];
        vector<int> fs;
        for (const auto kv : fs_m) {
            if (kv.first == '-') continue;
            fs.push_back(kv.second);
        }

        if (unkn == 1) return sz(fs);

        if (unkn == 2 &&
            all_of(xbegin(fs), xend(fs), [](const int f) { return f == 2; })) {
            return sz(fs) + 1;
        }

        return inof(count(xbegin(fs), xend(fs), 2));
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = OptimalMemoryGame{}.findPairs("----------");
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = OptimalMemoryGame{}.findPairs("--------A----E-----IAO----U---");
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = OptimalMemoryGame{}.findPairs("-X");
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("Example A") {
        const auto actual = OptimalMemoryGame{}.findPairs("AA--BB");
        const auto expected = 3;
        EXPECT(actual == expected);
    },
    CASE("Example B") {
        const auto actual = OptimalMemoryGame{}.findPairs("--");
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("Example C") {
        const auto actual = OptimalMemoryGame{}.findPairs("A-B-");
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example D") {
        const auto actual = OptimalMemoryGame{}.findPairs("A-BBCC");
        const auto expected = 3;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
