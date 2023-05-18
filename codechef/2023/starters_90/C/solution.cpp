#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool can_change(const vector<ll> &ds, const ll N) {
    ll r = N;
    for (const auto d : ds) r %= d;
    return r == 0LL;
}

bool is_possible(const ll M, const ll N) {
    if (M == N) return true;
    if (M < N) return false;
    if (M % 2LL == 1LL) return false;

    vector<ll> ds;
    ll cur = M;
    while (cur % 2L == 0) {
        ds.push_back(cur / 2);
        cur /= 2;
    }

    return can_change(ds, N);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        ll M, N;
        cin >> M >> N;

        cout << (is_possible(M, N) ? "YES" : "NO") << '\n';
    }

    return 0;
}
