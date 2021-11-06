#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

namespace {
using Int = long long;

static const Int P = 1000LL * 1000LL * 1000LL + 7LL;
int intprj(const Int x) { return static_cast<int>(x % P); }

Int count_recur(const Int n) {
    if (n == 1LL) return 1LL;
    const Int m = (2LL * (n - 1LL) + 1LL) % P;
    return (count_recur(n - 1LL) * (((m + m * m) / 2LL) % P)) % P;
}
} // namespace

struct Solution final {
    int countOrders(const int n) const { return intprj(count_recur(n)); }
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

int main(int argc, char **argv) {
    cout << Solution{}.countOrders(500) << '\n';
    return lest::run(tests, argc, argv);
}
