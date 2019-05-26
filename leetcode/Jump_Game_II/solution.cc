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

int intof(const size_t x) { return static_cast<int>(x); }

int Solution::jump(const vector<int> &xs) const {
    if (!xs.size()) return 0;

    int first = 0;
    int last = 0;
    int result = 0;

    for (;;) {
        int max_reach = -1;

        for (int i = first; i <= last; ++i) {
            if (i == intof(xs.size()) - 1) return result;

            max_reach = max(max_reach, i + xs[i]);
        }

        first = last + 1;
        last = max_reach;
        ++result;
    }

    throw logic_error("The last element is assumed to be always reachable");
}

// clang-format off
const lest::test tests[] = {
    CASE("is 0 on an empty vector") {
        const int actual = Solution().jump({});
        const int expected = 0;
        EXPECT(actual == expected);
    },
    CASE("is 0 on a 1-element vector") {
        const int actual = Solution().jump({1});
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
