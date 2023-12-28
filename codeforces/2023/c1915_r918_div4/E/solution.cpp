#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const vector<ll> &xs) {
    const auto n = sz(xs);
    vector<ll> evs(n, 0);
    vector<ll> ods(n, 0);
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            evs[i] = xs[i];
        } else {
            ods[i] = xs[i];
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<ll> xs(n);
        for (auto &x : xs) cin >> x;

        cout << (is_possible(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
