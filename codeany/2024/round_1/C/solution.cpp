#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pair<int, int> exp_of_2_and_odd_quotient(int x) {
    int e{};
    while (x % 2 == 0) {
        ++e;
        x /= 2;
    }
    return {e, x};
}

constexpr int mlog2(const ll x) {
    return 8 * sizeof(ll) - __builtin_clzll(x) - 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> xs(n);
    for (auto &x : xs) cin >> x;
    ll result = *max_element(cbegin(xs), cend(xs));

    map<ll, ll> fq;
    for (const auto x : xs) {
        const auto [e, q] = exp_of_2_and_odd_quotient(x);
        fq[q] += 1 << e;
    }

    for (const auto &[x, f] : fq) {
        const auto e = mlog2(f);
        result = max(result, x << e);
    }

    cout << result << '\n';
    return 0;
}
