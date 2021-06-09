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

vi full_a(const int N, const vi &Aprefix) {
    vector<int> A(N);
    const int L = sz(Aprefix);
    for (int i = 0; i < L; ++i) A[i] = Aprefix[i];
    for (int i = L; i < N; ++i) {
        A[i] = inof((A[i - 1] * 1103515245LL + 12345LL) % (1LL << 31));
    }
    return A;
}

vi digits(int x) {
    vector<int> ds;
    while (x) {
        ds.push_back(x % 10);
        x /= 10;
    }

    vi ans(10, 0);
    for (int i = 0; i < min(10, sz(ds)); ++i) {
        ans[i] = ds[i];
    }
    return ans;
}

struct DistancesBetweenNumbers final {
    ll count(const int n, const vi &prefix) const {
        const auto a = full_a(n, prefix);
        vvi idx(10, vi(10, 0));

        for (const auto x : a) {
            const auto ds = digits(x);
            for (int i = 0; i < 10; ++i) ++idx[i][ds[i]];
        }

        const auto num_others = [&](const int i, const int d) -> int {
            int ans = 0;

            for (int j = 0; j < 10; ++j) {
                if (j == d) continue;
                ans += idx[i][j];
            }

            return ans;
        };

        ll ans = 0;

        for (int i = 0; i < n; ++i) {
            for (int d = 0; d < 10; ++d) {
                ans += llof(idx[i][d]) * llof(num_others(i, d));
            }
        }

        return ans / 2LL;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = DistancesBetweenNumbers{}.count(4, {47, 47, 47, 47});
        const auto expected = 0LL;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = DistancesBetweenNumbers{}.count(4, {47, 47, 42, 47});
        const auto expected = 3LL;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = DistancesBetweenNumbers{}.count(4, {1, 10, 100, 1000});
        const auto expected = 12LL;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = DistancesBetweenNumbers{}.count(10, {1234567, 1234890});
        const auto expected = 389LL;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
