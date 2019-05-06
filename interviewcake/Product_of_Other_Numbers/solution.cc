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

vector<int> products_of_others(const vector<int> &xs) {
    if (xs.size() < 2) throw invalid_argument("At least 2 ints required");

    vector<int> res(xs.size(), 1);
    for (size_t i = 1; i != xs.size(); ++i) res[i] = res[i - 1] * xs[i - 1];

    int prod = 1;

    for (auto i = ++(xs.crbegin()); i != xs.crend(); ++i) {
        const size_t xs_idx = xs.size() - distance(xs.crbegin(), i);
        prod *= xs[xs_idx];
        res[xs_idx] *= prod;
    }

    return res;
}

// clang-format off
const lest::test tests[] = {
    CASE("small vector") {
        const auto actual = products_of_others({1, 2, 3});
        const auto expected = vector<int> {6, 3, 2};
        EXPECT(actual == expected);
    },

    CASE("longer vector") {
        const auto actual = products_of_others({8, 2, 4, 3, 1, 5});
        const auto expected = vector<int> {120, 480, 240, 320, 960, 192};
        EXPECT(actual == expected);
    },

    CASE("vector has one zero") {
        const auto actual = products_of_others({6, 2, 0, 3});
        const auto expected = vector<int> {0, 0, 36, 0};
        EXPECT(actual == expected);
    },

    CASE("vector has two zeros") {
        const auto actual = products_of_others({4, 0, 9, 1, 0});
        const auto expected = vector<int> {0, 0, 0, 0, 0};
        EXPECT(actual == expected);
    },

    CASE("one negative number") {
        const auto actual = products_of_others({-3, 8, 4});
        const auto expected = vector<int> {32, -12, -24};
        EXPECT(actual == expected);
    },

    CASE("all negative numbers") {
        const auto actual = products_of_others({-7, -1, -4, -2});
        const auto expected = vector<int> {-8, -56, -14, -28};
        EXPECT(actual == expected);
    },

    CASE("error with empty vector") {
        EXPECT_THROWS(products_of_others({}));
    },

    CASE("error with one number") {
        EXPECT_THROWS(products_of_others({1}));
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
