#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    int longestStrChain(const vector<string> &words) { return -1; }
};

// clang-format off
const lest::test tests[] = {
    CASE("Problem statement example 1") {
        const auto actual = Solution{}.longestStrChain({"a","b","ba","bca","bda","bdca"});
        const auto expected = 4;
        EXPECT(actual == expected);
    },
    CASE("a, b") {
        const auto actual = Solution{}.longestStrChain({"a","b"});
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("xy, x, xyz, y, v, mmm, ddd, f, g, h") {
        const auto actual = Solution{}.longestStrChain({"xy","x","xyz","y","v","mmm","ddd","f","g","h"});
        const auto expected = 3;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
