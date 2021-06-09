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

struct ContainsItsAverage final {
    vi missing(const vi &xs) const {
        const int s = accumulate(xs.cbegin(), xs.cend(), 0);
        const int n = sz(xs) + 1;

        set<int> ans;
        if (s % (n - 1) == 0) ans.insert(s / (n - 1));

        for (const auto x : xs) {
            ans.insert((n - 1) * x - (s - x));
        }

        return vi(ans.cbegin(), ans.cend());
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = ContainsItsAverage{}.missing({0, 0, 0});
        const auto expected = vi{0};
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = ContainsItsAverage{}.missing({1, 10, 1000, 100});
        const auto expected = vi{-1106, -1061, -611, 3889 };
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = ContainsItsAverage{}.missing({500000, 400000, 200000, 100000});
        const auto expected = vi {-700000, -200000, 300000, 800000, 1300000};
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = ContainsItsAverage{}.missing({47});
        const auto expected = vi{47};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
