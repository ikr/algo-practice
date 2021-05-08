#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

struct CubeTower final {
    ll difference(const ll H, const ll N) const {
        const ll v_lo = [=]() -> ll {
            if (H % N == 0) {
                const ll d = H / N;
                return N * (d * d * d);
            }

            {
                const ll d = div_ceil(H, N);
                const ll dd = H - (N - 1) * d;
                if (dd > 0) return (N - 1) * (d * d * d) + dd * dd * dd;
            }

            const ll d = H / N;
            const ll dd = H - (N - 1) * d;
            return (N - 1) * (d * d * d) + dd * dd * dd;
        }();

        const ll D = H - (N - 1);
        const ll v_hi = N - 1 + D * D * D;

        return v_hi - v_lo;
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
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
