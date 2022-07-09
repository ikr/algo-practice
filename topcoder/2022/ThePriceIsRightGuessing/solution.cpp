#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

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

struct ThePriceIsRightGuessing final {
    ll guess(vector<ll> xs, const ll M) const {
        sort(begin(xs), end(xs));

        set<ll> yss;
        if (xs.empty() || xs[0] != 1) yss.insert(1);

        for (int i = 0; i < sz(xs) - 1; ++i) {
            if (xs[i] + 1 != xs[i + 1]) {
                yss.insert(xs[i] + 1);
            }
        }

        if (!xs.empty() && xs.back() < M) yss.insert(xs.back() + 1);

        ll hi = LONG_LONG_MIN;
        ll result = -1;

        for (const auto y : yss) {
            const auto it = upper_bound(xbegin(xs), xend(xs), y);
            if (it == xend(xs)) {
                if (M - y + 1 > hi) {
                    result = y;
                    hi = M - y;
                }
            } else {
                if (*it - y + 1 > hi) {
                    result = y;
                    hi = *it - y + 1;
                }
            }
        }

        return result;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = ThePriceIsRightGuessing{}.guess({1, 3, 5, 7, 9}, 10LL);
        const auto expected = 2LL;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = ThePriceIsRightGuessing{}.guess({}, 47LL);
        const auto expected = 1LL;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = ThePriceIsRightGuessing{}.guess({100000000000LL, 300000000000LL, 500000000000LL, 700000000000LL, 900000000000LL}, 1000000000000LL);
        const auto expected = 100000000001LL;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = ThePriceIsRightGuessing{}.guess({1, 9, 5, 2, 4, 10, 7, 3, 8}, 10);
        const auto expected = 6LL;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = ThePriceIsRightGuessing{}.guess({1, 10}, 20);
        const auto expected = 11LL;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
