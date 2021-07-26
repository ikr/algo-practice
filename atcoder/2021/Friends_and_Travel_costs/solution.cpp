#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll reach_index(ll balance, const vector<pair<ll, ll>> &ab) {
    ll i = 0;

    for (const auto [j, v] : ab) {
        const bool can_reach = i + balance >= j;
        if (!can_reach) break;

        balance -= j - i;
        balance += v;
        i = j;
    }

    return i + balance;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll n, k;
    cin >> n >> k;

    vector<pair<ll, ll>> ab(n);
    for (auto &[a, b] : ab) cin >> a >> b;

    sort(begin(ab), end(ab));
    cout << reach_index(k, ab) << '\n';
    return 0;
}
