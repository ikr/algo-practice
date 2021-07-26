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

vll dist(const vi &a, const ll k) {
    const int n = sz(a);
    vi idx(n, 0);
    iota(begin(idx), end(idx), 0);
    sort(begin(idx), end(idx),
         [&](const int i, const int j) { return a[i] < a[j]; });

    vll ans(n, k / llof(n));

    for (int i = 0; i < inof(k % llof(n)); ++i) {
        ++ans[idx[i]];
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    ll k;
    cin >> n >> k;

    vi a(n);
    for (auto &x : a) cin >> x;

    const auto ans = dist(a, k);
    for (const auto x : ans) cout << x << '\n';

    return 0;
}
