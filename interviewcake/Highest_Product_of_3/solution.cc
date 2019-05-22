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

void stack_rate_indices(function<bool(const int, const int)> compare,
                        const vector<int> &xs, vector<size_t> &indices,
                        const size_t candidate_index) {
    indices.push_back(candidate_index);

    sort(indices.begin(), indices.end(),
         [compare, xs](const size_t i, const size_t j) {
             return compare(xs[i], xs[j]);
         });

    indices.pop_back();
}

int candidate_result(const vector<int> &xs, vector<size_t> &max_3_indices,
                     vector<size_t> &min_3_indices, const size_t x_index) {
    int result = numeric_limits<int>::min();

    for (auto indices : {max_3_indices, min_3_indices}) {
        auto i = find(indices.begin(), indices.end(), x_index);
        if (i == indices.end()) indices.back() = x_index;

        result = max(result, accumulate(indices.begin(), indices.end(), 1,
                                        [xs](const int memo, const size_t j) {
                                            return memo * xs[j];
                                        }));
    }

    return result;
}

int highestProductOf3(const vector<int> &xs) {
    if (xs.size() < 3) throw invalid_argument("At least 3 expected");

    vector<size_t> max_3_indices = {0, 1, 2};
    vector<size_t> min_3_indices(max_3_indices);

    for (size_t i = 3; i != xs.size(); ++i) {
        stack_rate_indices(greater_equal<int>(), xs, max_3_indices, i);
        stack_rate_indices(less<int>(), xs, min_3_indices, i);
    }

    int result = numeric_limits<int>::min();

    for (size_t i = 0; i != xs.size(); ++i) {
        result =
            max(result, candidate_result(xs, max_3_indices, min_3_indices, i));
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
