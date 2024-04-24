#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using ll = long long;
static constexpr ll M = 1e9 + 7;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_s(const vector<ll> &xs) {
    const auto n = sz(xs);
    if (n == 1) return xs[0];
    vector<ll> ss(n);
    partial_sum(cbegin(xs), cend(xs), begin(ss));

    int i0 = 1;
    ll hi = xs[0] * xs[1];

    for (int i = 2; i < n; ++i) {
        if (ss[i - 1] * xs[i] >= ss[i]) {
            i0 = i;
            hi = ss[i - 1] * xs[i];
            break;
        }
    }

    // cerr << xs << " i0:" << i0 << " hi:" << hi << endl;

    ll result = hi % M;
    for (int i = i0 + 1; i < n; ++i) {
        result *= xs[i];
        result %= M;
    }
    return result;
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
