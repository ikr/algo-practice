#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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

ll ma_pow(ll b, ll e) {
    ll ans = 1;
    for (; e; b = b * b, e /= 2) {
        if (e & 1) ans = ans * b;
    }
    return ans;
}

struct CarryAOne final {
    ll count(const int B, const int D) const {
        auto total_D_nums = (B - 1LL) * ma_pow(B, D - 1);
        total_D_nums *= total_D_nums;

        ll cell0{};
        for (ll i = 1LL; i <= B - 1LL; ++i) {
            cell0 += B - 1LL - i;
        }

        ll cell_{};
        for (ll i = 0LL; i <= B - 1LL; ++i) {
            cell_ += B - 1LL - i;
        }

        ll no_carry = cell0;
        for (int i = 1; i < D; ++i) {
            no_carry *= cell_;
        }

        return total_D_nums - no_carry;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = CarryAOne{}.count(10, 1);
        const auto expected = 45LL;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = CarryAOne{}.count(2, 5);
        const auto expected = 256LL;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = CarryAOne{}.count(6, 3);
        const auto expected = 27990LL;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
