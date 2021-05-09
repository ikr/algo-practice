#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll volume_hi(const ll H, const ll N) {
    const ll D = H - (N - 1);
    return N - 1 + D * D * D;
}

constexpr ll cube(const ll x) { return x * x * x; }

ll volume_lo(const ll H, const ll N) {
    const ll r = H % N;

    if (r == 0) {
        const ll d = H / N;
        return N * cube(d);
    }

    const ll d = H / N;
    return (N - r) * cube(d) + r * cube(d + 1);
}

struct CubeTower final {
    ll difference(const ll H, const ll N) const {
        return volume_hi(H, N) - volume_lo(H, N);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = CubeTower{}.difference(4, 2);
        const auto expected = 12;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = CubeTower{}.difference(17, 16);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = CubeTower{}.difference(5, 3);
        const auto expected = 12;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = CubeTower{}.difference(9, 3);
        const auto expected = 264;
        EXPECT(actual == expected);
    },
    CASE("Case 1 1") {
        const auto actual = CubeTower{}.difference(1, 1);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Case 5 2") {
        const auto actual = CubeTower{}.difference(5, 2);
        const auto expected = 4 * 4 * 4 + 1 - 2 * 2 * 2 - 3 * 3 * 3;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
