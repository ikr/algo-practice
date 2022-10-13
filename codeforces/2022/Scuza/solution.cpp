#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<ll> answer_queries(const vector<ll> &xs, const vector<ll> &ks) {
    vector<ll> hi(sz(xs), xs[0]);
    for (int i = 1; i < sz(hi); ++i) {
        hi[i] = max(hi[i - 1], xs[i]);
    }

    vector<ll> ss(sz(xs));
    partial_sum(cbegin(xs), cend(xs), begin(ss));

    vector<ll> result;
    result.reserve(sz(xs));

    for (const auto k : ks) {
        const auto it = upper_bound(cbegin(hi), cend(hi), k);

        if (it == cbegin(hi)) {
            result.push_back(0);
            continue;
        }

        const auto i = inof(distance(cbegin(hi), prev(it)));
        result.push_back(ss[i]);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<ll> xs(n);
        for (auto &x : xs) cin >> x;

        vector<ll> ks(q);
        for (auto &k : ks) cin >> k;

        cout << answer_queries(xs, ks) << '\n';
    }

    return 0;
}
