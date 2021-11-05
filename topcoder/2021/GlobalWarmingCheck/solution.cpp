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

string::const_iterator cbegin(const string &xs) { return xs.cbegin(); }
string::const_iterator cend(const string &xs) { return xs.cend(); }

vll gather_ts(const ll N, const ll M) {
    vll ans(N);
    for (ll i = 0; i < N; ++i) {
        ans[i] = (i * i + 4LL * i + 7LL) % M;
    }
    return ans;
}

struct GlobalWarmingCheck final {
    vi solve(const int N, const int M, const int Y) const {
        const auto ts = gather_ts(N, M);
        set<pair<ll, int>> ai;

        ll curr = accumulate(cbegin(ts), cbegin(ts) + Y, 0LL);
        ai.emplace(curr, 0);

        for (int i = 1; i + Y <= N; ++i) {
            curr -= ts[i - 1];
            curr += ts[i + Y - 1];
            ai.emplace(curr, i);
        }

        return {ai.cbegin()->second, ai.crbegin()->second};
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = GlobalWarmingCheck{}.solve(12, 20, 1);
        const auto expected = vi{8, 4};
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = GlobalWarmingCheck{}.solve(12, 20, 4);
        const auto expected = vi{6, 2};
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = GlobalWarmingCheck{}.solve(12, 1, 3);
        const auto expected = vi{0, 9};
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = GlobalWarmingCheck{}.solve(57000, 997, 23);
        const auto expected = vi{984, 56322};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
