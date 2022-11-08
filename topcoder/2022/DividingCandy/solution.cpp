#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static constexpr ll HI = 100000;

ll one_kind_divide(const ll C, const ll N) {
    assert(N > 0LL);
    const auto q = C / N;

    if (q > HI) {
        return C - HI * N;
    }

    if (q == 0LL) return -1;
    return C % N;
}

struct DividingCandy final {
    ll divide(const ll C, const ll L, const ll D) const {
        if (!L) return one_kind_divide(C, D);
        if (!D) return one_kind_divide(C, L);
        if (2 * L + D > C) return -1;

        ll ans{LONG_LONG_MAX};

        for (ll k = 2; k <= HI; ++k) {
            const auto C_ = C - k * L;
            if (C_ <= 0LL) continue;

            const auto q = C_ / D;
            if (q >= k) {
                ans = min(ans, C_ - (D * (k - 1)));
                continue;
            }

            if (q == 0LL) continue;
            ans = min(ans, C_ % D);
        }

        return (ans == LONG_LONG_MAX) ? -1 : ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = DividingCandy{}.divide(80, 10, 10);
        const auto expected = 0LL;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = DividingCandy{}.divide(27, 20, 10);
        const auto expected = -1LL;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = DividingCandy{}.divide(9876543210LL, 0, 2);
        const auto expected = 9876343210LL;
        EXPECT(actual == expected);
    },
    CASE("Example 6") {
        const auto actual = DividingCandy{}.divide(200001, 1, 1);
        const auto expected = 2LL;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
