#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

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

static const vector<ll> PS{1, 10, 100, 1000, 10000, 100000, 1000000};

struct DecimalCoins final {
    int pay(const vi &xs) const {
        if (xs[0] == 0) return 1;
        ll s = xs[0];

        for (int i = 1; i < sz(PS); ++i) {
            if (xs[i] > 0 && s + 1LL < 0LL + PS[i]) return inof(s + 1);
            s += PS[i] * xs[i];
        }

        return inof(s + 1);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = DecimalCoins{}.pay({7, 3, 1, 0, 0, 0, 0});
        const auto expected = 8;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = DecimalCoins{}.pay({123, 1, 0, 0, 0, 0, 0});
        const auto expected = 134;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
