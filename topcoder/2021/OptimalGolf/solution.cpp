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

template <typename T>
constexpr typename vector<T>::const_iterator cbegin(const vector<T> &xs) {
    return xs.cbegin();
}

template <typename T>
constexpr typename vector<T>::const_iterator cend(const vector<T> &xs) {
    return xs.cend();
}

struct OptimalGolf final {
    int minStrokes(const int d, const vi &lo, const vi &hi) const {
        if (d == 0) return 0;

        for (int i = 0; i < sz(lo); ++i) {
            if (lo[i] <= d && d <= hi[i]) return 1;
        }

        for (int i = 0; i < sz(lo); ++i) {
            for (int x = lo[i]; x <= hi[i]; ++x) {
                if (d < 2 * x) return 2;
            }
        }

        const auto longest = *max_element(cbegin(hi), cend(hi));
        assert(d > longest);
        return 1 + minStrokes(d - longest, lo, hi);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = OptimalGolf{}.minStrokes(7, {1}, {1});
        const auto expected = 7;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = OptimalGolf{}.minStrokes(7, {2}, {2});
        const auto expected = 4;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = OptimalGolf{}.minStrokes(470, {100, 400, 600}, {200, 500, 700});
        const auto expected = 1;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = OptimalGolf{}.minStrokes(47, {5, 4, 2}, {5, 7, 10});
        const auto expected = 5;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = OptimalGolf{}.minStrokes(3, {7}, {100});
        const auto expected = 2;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
