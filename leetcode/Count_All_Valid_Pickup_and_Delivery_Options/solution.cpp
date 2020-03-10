#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    int countOrders(const int n) const {
        return n;
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
