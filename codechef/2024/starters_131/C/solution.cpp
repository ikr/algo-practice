#include <bits/stdc++.h>
using namespace std;

using ll = long long;
static constexpr ll M = 1e9 + 7;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_s(const vector<ll> &xs) {
    const auto n = sz(xs);
    if (n == 1) return xs[0];

    int ir{};
    ll s{};
    if (xs[0] == 1) {
        while (ir + 1 < n && xs[ir + 1] == 1) ++ir;
        s = ir + 1;
    } else {
        s = xs[0];
    }

    for (int i = ir + 1; i < n; ++i) {
        s *= xs[i];
        s %= M;
    }
    return s;
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
        sort(begin(xs), end(xs));
        cout << max_s(xs) << endl;
    }

    return 0;
}
