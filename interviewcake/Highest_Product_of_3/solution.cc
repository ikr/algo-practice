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

int highestProductOf3(const vector<int>& xs)
{
    return static_cast<int>(xs.size());
}

// clang-format off
const lest::test tests[] = {
    CASE("short vector") {
        const int actual = highestProductOf3({1, 2, 3, 4});
        const int expected = 24;
        EXPECT(actual == expected);
    },

    CASE("longer vector") {
        const int actual = highestProductOf3({6, 1, 3, 5, 7, 8, 2});
        const int expected = 336;
        EXPECT(actual == expected);
    },

    CASE("vector has one negative") {
        const int actual = highestProductOf3({-5, 4, 8, 2, 3});
        const int expected = 96;
        EXPECT(actual == expected);
    },

    CASE("vector has two negatives") {
        const int actual = highestProductOf3({-10, 1, 3, 2, -10});
        const int expected = 300;
        EXPECT(actual == expected);
    },

    CASE("vector is all negatives") {
        const int actual = highestProductOf3({-5, -1, -3, -2});
        const int expected = -6;
        EXPECT(actual == expected);
    },

    CASE("exception with empty vector") {
        EXPECT_THROWS(highestProductOf3({}));
    },

    CASE("exception with one number") {
        EXPECT_THROWS(highestProductOf3({1}));
    },

    CASE("exception with two numbers") {
        EXPECT_THROWS(highestProductOf3({1, 1}));
    },
};
// clang-format on

int main(int argc, char** argv) {
    return lest::run(tests, argc, argv);
}
