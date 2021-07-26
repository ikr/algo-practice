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

struct BallotCounting final {
    int count(const string &xs) const {
        int a = 0;
        int b = 0;

        for (int i = 0; i < sz(xs); ++i) {
            if (xs[i] == 'A') {
                ++a;
            } else {
                ++b;
            }

            if (a > sz(xs) / 2 || b > sz(xs) / 2) return i + 1;
        }

        return sz(xs);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = BallotCounting{}.count("AAAAABBBBB");
        const auto expected = 10;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = BallotCounting{}.count("AAAAABBBBA");
        const auto expected = 10;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = BallotCounting{}.count("AAAAA");
        const auto expected = 3;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
