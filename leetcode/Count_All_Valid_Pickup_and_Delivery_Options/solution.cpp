#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

namespace {
using Int = long long;
}

struct Solution final {
    int countOrders(const int n) const {
        if (n == 1) return 1;
        const int m = 2 * (n - 1) + 1;
        return countOrders(n - 1) * (m + m * m) / 2;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 1") {
        const auto actual = Solution{}.countOrders(1);
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = Solution{}.countOrders(2);
        const auto expected = 6;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = Solution{}.countOrders(3);
        const auto expected = 90;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
