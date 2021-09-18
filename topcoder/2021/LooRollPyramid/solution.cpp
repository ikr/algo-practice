#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
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

string::const_iterator cbegin(const string &xs) { return xs.cbegin(); }
string::const_iterator cend(const string &xs) { return xs.cend(); }

int solve(const ll a, const ll b) {
    if (!b) return 0;

    const auto ut = [&](const ll k) -> ll {
        return ((k + 1) * (2 * a - k)) / 2;
    };

    ll lo = 0;
    ll hi = a - 1;

    if (ut(lo) >= b) return inof(ut(lo) - b);
    if (ut(hi) == b) return 0;

    while (lo < hi) {
        const ll mid = lo + (hi - lo) / 2LL;

        if (ut(mid) >= b) {
            hi = mid;
        } else {
            lo = mid;
        }

        if (hi == lo + 1) break;
    }

    return inof(ut(hi) - b);
}

struct LooRollPyramid final {
    vi countMissing(const int q, const vi &a, const vll &b) const {
        vi ans(q, 0);

        for (int i = 0; i < q; ++i) {
            ans[i] = solve(a[i], b[i]);
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("debug") {
        EXPECT(2 == solve(5, 10));
    },
    CASE("Example 0") {
        const auto actual = LooRollPyramid{}.countMissing(4, {5, 5, 5, 5}, {15, 10, 5, 0});
        const auto expected = vi{0, 2, 0, 0 };
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = LooRollPyramid{}.countMissing(5, {4, 5, 6, 7, 8}, {10, 10, 10, 10, 10});
        const auto expected = vi{0, 2, 1, 3, 5 };
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = LooRollPyramid{}.countMissing(
            10,
            {987654321, 987654321, 987654321, 987654321, 987654321, 987654321, 987654321, 987654321, 987654321, 987654321},
            {5432109876543210, 5432109876543211, 5432109876543212, 5432109876543213, 5432109876543214, 5432109876543215, 5432109876543216, 5432109876543217, 5432109876543218, 5432109876543219}
        );
        const auto expected = vi{735344876, 735344875, 735344874, 735344873, 735344872, 735344871, 735344870, 735344869, 735344868, 735344867};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
