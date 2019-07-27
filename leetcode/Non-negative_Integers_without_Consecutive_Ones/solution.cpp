#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

constexpr bool cons_ones(const int x) {
    return (3 & x) == 3 || ((x >> 1) & x) != 0;
}

struct Solution final {
    int findIntegers(int num) const {
        int ans{0};

        for (int i = 0; i <= num; ++i) {
            if (!cons_ones(i)) ++ans;
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Problem statement example") {
        const auto actual = Solution().findIntegers(5);
        const auto expected = 5;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
