#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll volume_hi(const ll H, const ll N) {
    const ll D = H - (N - 1);
    return N - 1 + D * D * D;
}

ll volume_lo(const ll H, const ll N) {
    if (H % N == 0) {
        const ll d = H / N;
        return N * (d * d * d);
    }

    const auto fair = [=](const ll h, const ll n) -> ll {
        const ll d = h / n;
        const ll dd = h - (n - 1) * d;
        return (n - 1) * d * d * d + dd * dd * dd;
    };

    const ll o1 = fair(H, N);

    const ll o2 = [=]() -> ll {
        const ll d = H / N + 1;
        const ll k = H / d;

        return k * (d * d * d) + ((N - k) ? volume_lo(H - k * d, N - k) : 0);
    }();

    return min(o1, o2);
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
