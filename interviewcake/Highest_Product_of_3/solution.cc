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

void stack_rate(vector<int> &xs, const int candidate,
                function<bool(const int, const int)> compare) {
    xs.push_back(candidate);
    sort(xs.begin(), xs.end(), compare);
    xs.pop_back();
}

int candidate_result(const vector<int> &max_2, const vector<int> &min_2,
                     const int x) {
    return max(accumulate(max_2.begin(), max_2.end(), 1, multiplies<int>()) * x,
               accumulate(min_2.begin(), min_2.end(), 1, multiplies<int>()) *
                   x);
}

int highestProductOf3(const vector<int> &xs) {
    if (xs.size() < 3) throw invalid_argument("At least 3 expected");

    vector<int> max_2(xs.begin(), xs.begin() + 2);
    vector<int> min_2(max_2);
    int result = candidate_result(max_2, min_2, *(xs.begin() + 2));

    for (auto i = xs.begin() + 2; i != xs.end(); ++i) {
        const int y = candidate_result(max_2, min_2, *i);
        if (y > result) result = y;
        stack_rate(max_2, *i, greater<int>());
        stack_rate(min_2, *i, less<int>());
    }

    return result;
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
