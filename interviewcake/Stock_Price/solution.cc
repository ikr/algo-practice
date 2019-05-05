#include "lest.hpp"
#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <locale>
#include <numeric>
#include <optional>
#include <set>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int max_profit_from(const vector<int> &prices) {
    if (prices.size() < 2)
        throw invalid_argument("Expecting at least 2 prices");

    int min_so_far = INT_MAX;
    int max_profit = INT_MIN;

    for (const int x : prices) {
        if (min_so_far == INT_MAX) {
            min_so_far = x;
            continue;
        }

        const int profit = x - min_so_far;
        if (profit > max_profit) max_profit = profit;
        if (x < min_so_far) min_so_far = x;
    }

    return max_profit;
}

// clang-format off
const lest::test tests[] = {
    CASE("price goes up then down") {
        const int actual = max_profit_from({1, 5, 3, 2});
        const int expected = 4;
        EXPECT(actual == expected);
    },

    CASE("price goes down then up") {
        const int actual = max_profit_from({7, 2, 8, 9});
        const int expected = 7;
        EXPECT(actual == expected);
    },

    CASE("price goes up all day") {
        const int actual = max_profit_from({1, 6, 7, 9});
        const int expected = 8;
        EXPECT(actual == expected);
    },

    CASE("price goes down all day") {
        const int actual = max_profit_from({9, 7, 4, 1});
        const int expected = -2;
        EXPECT(actual == expected);
    },

    CASE("price stays the same all day") {
        const int actual = max_profit_from({1, 1, 1, 1});
        const int expected = 0;
        EXPECT(actual == expected);
    },

    CASE("exception with empty prices") {
        EXPECT_THROWS(max_profit_from({}));
    },

    CASE("exception with one price") {
        EXPECT_THROWS(max_profit_from({1}));
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
