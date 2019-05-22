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

struct Solution {
    int jump(const vector<int> &xs) const;
};

int Solution::jump(const vector<int> &xs) const {
    return static_cast<int>(xs.size());
}

// clang-format off
const lest::test tests[] = {
    CASE("Just returns 0") {
        const int actual = Solution().jump({});
        const int expected = 0;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
