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

size_t min_jumps(const Iter rbegin, const Iter rend) {
    if (distance(rbegin, rend) == 1) return 0;

    size_t result = numeric_limits<size_t>::max();

    for (auto i = rbegin + 1; i != rend; ++i) {
        const size_t d = distance(rbegin, i);
        if (d > *i) continue;

        const size_t candidate = 1 + min_jumps(i, rend);
        if (candidate < result) result = candidate;
    }

    return result;
}

struct Solution {
    int jump(const vector<int> &xs) const;
};

int Solution::jump(const vector<int> &xs) const {
    if (!xs.size()) return 0;

    vector<size_t> non_negatives(xs.size());
    copy(xs.begin(), xs.end(), non_negatives.begin());

    return static_cast<int>(
        min_jumps(non_negatives.rbegin(), non_negatives.rend()));
}

// clang-format off
const lest::test tests[] = {
    CASE("is 0 on an empty vector") {
        const int actual = Solution().jump({});
        const int expected = 0;
        EXPECT(actual == expected);
    },
    CASE("is 2 on 2,3,1,1,4") {
        const int actual = Solution().jump({2,3,1,1,4});
        const int expected = 2;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
