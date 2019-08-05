#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

using ui_t = unsigned int;

struct Solution final {
    bool canMeasureWater(const ui_t x, const ui_t y, const ui_t z) const {
        if (z == x || z == y || z == x + y || z == 0U) return true;
        if (z > x + y) return false;
        return z % gcd(x, y) == 0U;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Problem statement example 1") {
        const auto actual = Solution().canMeasureWater(3, 5, 4);
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("Problem statement example 2") {
        const auto actual = Solution().canMeasureWater(2, 6, 5);
        const auto expected = false;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
