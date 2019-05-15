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

void stack_rate(std::vector<int> &xs, const int candidate,
                std::function<bool(const int, const int)> compare) {
    xs.push_back(candidate);
    sort(xs.begin(), xs.end(), compare);
    xs.erase(xs.end() - 1);
}

int highestProductOf3(const vector<int> &xs) {
    if (xs.size() < 3) throw invalid_argument("At least 3 expected");

    vector<int> max_3(xs.begin(), xs.begin() + 3);
    sort(max_3.begin(), max_3.end(), std::greater<int>());

    vector<int> min_3(max_3);
    sort(min_3.begin(), min_3.end(), std::less<int>());

    for (auto i = xs.begin() + 3; i != xs.end(); ++i) {
        stack_rate(max_3, *i, std::greater<int>());
        stack_rate(min_3, *i, std::less<int>());
    }

    return max_3[0] * max_3[1] * max_3[2];
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

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
