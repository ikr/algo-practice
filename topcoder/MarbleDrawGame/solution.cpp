#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll factorial(const ll x) {
    assert(x >= 0);
    if (x <= 1) return 1;

    ll ans = 2;
    for (ll i = 3; i <= x; ++i) {
        ans *= i;
    }

    return ans;
}

ll combinations(const ll n, const ll k) {
    assert(k <= n);
    const ll r = n - k;
}

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

struct MarbleDrawGame final {
    double winningChance(const vector<int> &xs) const {
        const int m = accumulate(xs.cbegin(), xs.cend(), 0);
        double ans = 0.0;

        for (const int x : xs) {
            if (x < 5) continue;

            const int k = 9;

            for (int i0 = 0; i0 < k - 4; ++i0) {
                for (int i1 = i0 + 1; i1 < k - 3; ++i1) {
                    for (int i2 = i1 + 1; i2 < k - 2; ++i2) {
                        for (int i3 = i2 + 1; i3 < k - 1; ++i3) {
                            for (int i4 = i3 + 1; i4 < k; ++i4) {
                                double p = doof(x) / doof(m - i0);
                                p *= doof(x - 1) / doof(m - i1);
                                p *= doof(x - 2) / doof(m - i2);
                                p *= doof(x - 3) / doof(m - i3);
                                p *= doof(x - 4) / doof(m - i4);

                                ans += p;
                            }
                        }
                    }
                }
            }
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = MarbleDrawGame{}.winningChance({5, 5});
        const auto expected = 1.0;
        EXPECT(abs(actual - expected) < 1e-9);
    },
    CASE("Example 1") {
        const auto actual = MarbleDrawGame{}.winningChance({3, 4, 3});
        const auto expected = 0.0;
        EXPECT(abs(actual - expected) < 1e-9);
    },
    CASE("Example 2") {
        const auto actual = MarbleDrawGame{}.winningChance({1, 1, 1, 1, 1, 5});
        const auto expected = 0.5;
        EXPECT(abs(actual - expected) < 1e-9);
    },
    CASE("Example 3") {
        const auto actual = MarbleDrawGame{}.winningChance({3, 4, 5, 6});
        const auto expected = 0.08031674208144797;
        EXPECT(abs(actual - expected) < 1e-9);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
