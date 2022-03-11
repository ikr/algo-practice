#include "lest.hpp"
#include <array>
#include <cassert>
#include <iostream>
#include <map>
#include <string>
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
        const auto fs = [&]() {
            map<char, int> result{{'-', 0}};
            for (const auto x : xs) ++result[x];
            return result;
        }();

        const auto stat = [&]() {
            array<int, 3> result{fs.at('-'), 0, 0};
            for (const auto kv : fs) {
                if (kv.first == '-') continue;
                assert(kv.second == 1 || kv.second == 2);
                ++result[kv.second];
            }
            return result;
        }();

        if (stat[1] == 1 || (stat[1] == 0 && stat[0] == 2) ||
            stat[1] == stat[0]) {
            return sz(xs) / 2;
        }
        return stat[2];
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
        const auto expected = 2;
        EXPECT(actual == expected);
    },
    CASE("Example D") {
        const auto actual = OptimalMemoryGame{}.findPairs("A-BBCC");
        const auto expected = 3;
        EXPECT(actual == expected);
    },
    CASE("Example E") {
        const auto actual = OptimalMemoryGame{}.findPairs("AABBCC");
        const auto expected = 3;
        EXPECT(actual == expected);
    },
    CASE("Example F") {
        const auto actual = OptimalMemoryGame{}.findPairs("A-B-C-");
        const auto expected = 3;
        EXPECT(actual == expected);
    },
    CASE("Example G") {
        const auto actual = OptimalMemoryGame{}.findPairs("ABC-----");
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example H") {
        const auto actual = OptimalMemoryGame{}.findPairs("ABC---ZZ");
        const auto expected = 4;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
