#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_shiftable_by_k(const string &xs, const int k) {
    const auto n = sz(xs);
    assert(0 < k && k < n);
    for (int i = 0; i + k < n; ++i) {
        if (xs[i + k] != xs[i]) return false;
    }
    return true;
}

int min_shift(const string &xs) {
    const auto n = sz(xs);
    for (int k = 1; k < n; ++k) {
        if (is_shiftable_by_k(xs, k)) return k;
    }
    return n;
}

struct FrequentSubstring final {
    int maximize(const string &xs, const int H) const {
        const auto n = sz(xs);
        if (H < n) return 0;
        if (H == n) return 1;
        const auto k = min_shift(xs);
        if (k == n) return H / n;

        ll lo = 1;
        ll hi = H + 2;

        while (lo + 1LL < hi) {
            const auto mid = lo + (hi - lo) / 2LL;
            const auto H_ = n + k * mid;
            if (H_ <= H) {
                lo = mid;
            } else {
                hi = mid;
            }
        }

        return inof(lo + 1);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = FrequentSubstring{}.maximize("abc", 5);
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = FrequentSubstring{}.maximize("aaa", 5);
        const auto expected = 3;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
