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

constexpr ll regions_num(const ll a, const ll b) { return (a + 1) * (b + 1); }

struct DivideThePlane final {
    ll makeCuts(const int h, const int v, const ll n) const {
        const ll curr = regions_num(h, v);
        if (n <= curr) return 0;

        ll ans = 0;
        ll a = min(h, v);
        ll b = max(h, v);

        for (;;) {
            ++ans;
            ++a;
            if (regions_num(a, b) >= n) return ans;

            if (a > b) {
                swap(a, b);
            }
        }

        assert(false && "/o\\");
        return -1;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = DivideThePlane{}.makeCuts(0, 0, 1);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example 6") {
        const auto actual = DivideThePlane{}.makeCuts(4, 7, 12345);
        const auto expected = 210;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
