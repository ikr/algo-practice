#include "lest.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

using ll = long long;

struct ContestTraining final {
    vector<ll> practice(const ll H, const ll L, const ll dH, const ll dL,
                        const vector<ll> &qs) const {
        const auto num_days = [&](const ll p) -> ll {
            if (p <= dH) return 1;
            if (div_ceil(p, dH) <= H) return div_ceil(p, dH);
            if (p - (H * dH) <= dL) return H + 1;
            if (div_ceil(p - (H * dH), dL) <= L) {
                return H + div_ceil(p - (H * dH), dL);
            }

            const auto cycle_problems = H * dH + L * dL;
            const auto full_cycles = p / cycle_problems;
            const auto r = p % cycle_problems;
            if (!r) return full_cycles * (H + L);

            return full_cycles * (H + L) + [&]() -> ll {
                if (r <= dH) return 1;
                if (div_ceil(r, dH) <= H) return div_ceil(r, dH);
                if (r - (H * dH) <= dL) return H + 1;
                return H + div_ceil(r - (H * dH), dL);
            }();
        };

        vector<ll> result(sz(qs));
        transform(xbegin(qs), xend(qs), begin(result), num_days);
        return result;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = ContestTraining{}.practice(5, 2, 5, 1, {5, 21, 25, 26, 27, 28, 32, 43, 50});
        const auto expected = vector<ll>{1, 5, 5, 6, 7, 8, 8, 11, 12};
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = ContestTraining{}.practice(1, 1234567890LL, 10, 1, {7, 17, 18, 19, 20, 987654321LL, 987654322LL, 2345678901LL, 345678901234LL});
        const auto expected = vector<ll>{1, 8, 9, 10, 11, 987654312LL, 987654313LL, 2345678883LL, 345678898714LL};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
