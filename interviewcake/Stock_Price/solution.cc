#include "lest.hpp"
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <locale>
#include <numeric>
#include <optional>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int max_profit(const vector<int> &stock_prices) {
    return static_cast<int>(stock_prices.size());
}

// clang-format off
const lest::test tests[] = {
    CASE("price goes up then down") {
        const int actual = max_profit({1, 5, 3, 2});
        const int expected = 4;
        EXPECT(actual == expected);
    },

    CASE("price goes down then up") {
        const int actual = max_profit({7, 2, 8, 9});
        const int expected = 7;
        EXPECT(actual == expected);
    },

    CASE("price goes up all day") {
        const int actual = max_profit({1, 6, 7, 9});
        const int expected = 8;
        EXPECT(actual == expected);
    },

    CASE("price goes down all day") {
        const int actual = max_profit({9, 7, 4, 1});
        const int expected = -2;
        EXPECT(actual == expected);
    },

    CASE("price stays the same all day") {
        const int actual = max_profit({1, 1, 1, 1});
        const int expected = 0;
        EXPECT(actual == expected);
    },

    CASE("exception with empty prices") {
        EXPECT_THROWS(max_profit({}));
    },

    CASE("exception with one price") {
        EXPECT_THROWS(max_profit({1}));
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
