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

using Iter = vector<size_t>::const_reverse_iterator;
const size_t npos = numeric_limits<size_t>::max();

size_t min_jumps(const Iter rbegin, const Iter rend, vector<size_t> &cache) {
    if (distance(rbegin, rend) == 1) return 0;
    size_t result = npos;

    for (auto i = rbegin + 1; i != rend; ++i) {
        const long d = distance(rbegin, i);
        if (static_cast<size_t>(d) > *i) continue;

        const long cache_idx = distance(i, rend);

        if (cache[cache_idx] == npos) {
            cache[cache_idx] = min_jumps(i, rend, cache);
        }

        const size_t candidate = 1 + cache[cache_idx];
        if (candidate < result) result = candidate;
    }

    return result;
}

Iter last_leading_1_or_rend(const vector<size_t> &xs) {
    Iter i = xs.rend();
    while (i - 1 != xs.rbegin() && *(i - 1) == 1) --i;
    return i;
}

struct Solution {
    int jump(const vector<int> &xs) const;
};

int Solution::jump(const vector<int> &xs) const {
    if (!xs.size()) return 0;

    vector<size_t> non_negatives(xs.size());
    copy(xs.begin(), xs.end(), non_negatives.begin());
    vector<size_t> cache(xs.size(), npos);

    const Iter optimal_rend = last_leading_1_or_rend(non_negatives);

    return static_cast<int>(distance(optimal_rend, non_negatives.crend())) +
           static_cast<int>(
               min_jumps(non_negatives.rbegin(), optimal_rend, cache));
}

// clang-format off
const lest::test tests[] = {
    CASE("is 0 on an empty vector") {
        const int actual = Solution().jump({});
        const int expected = 0;
        EXPECT(actual == expected);
    },
    CASE("example from the problem statement") {
        const int actual = Solution().jump({2,3,1,1,4});
        const int expected = 2;
        EXPECT(actual == expected);
    },
    CASE("the minimal possible path") {
        const int actual = Solution().jump({1,0});
        const int expected = 1;
        EXPECT(actual == expected);
    },
    CASE("with zeroes, jumping progressively longer") {
        const int actual = Solution().jump({1,1,2,0,3,0,0,0});
        const int expected = 4;
        EXPECT(actual == expected);
    },
    CASE("trivial") {
        const int actual = Solution().jump({1,1,1,0});
        const int expected = 3;
        EXPECT(actual == expected);
    },
    CASE("with a seemingly fast first jump") {
        const int actual = Solution().jump({5,1,1,1,2,0,2,1,0});
        const int expected = 3;
        EXPECT(actual == expected);
    },
    CASE("with a seemingly fast first jump") {
        const int actual = Solution().jump({5,6,4,4,6,9,4,4,7,4,4,8,2,6,8,1,5,9,6,5,2,7,9,7,9,6,9,4,1,6,8,8,4,4,2,0,3,8,5});
        const int expected = 5;
        EXPECT(actual == expected);
    },
    CASE("loads of 1-s") {
        const vector<int> xs(60000, 1);
        const int actual = Solution().jump(xs);
        const int expected = 59999;
        EXPECT(actual == expected);
    },
    CASE("25000 downto 0") {
        vector<int> xs(25002, 1);
        xs[0] = 0;
        iota(xs.begin() + 2, xs.end(), 1);
        reverse(xs.begin(), xs.end());

        const int actual = Solution().jump(xs);
        const int expected = 2;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
