#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

template <typename T> constexpr int llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int q;
    cin >> q;

    string s, t;
    cin >> s >> t;

    vector<pii> range_queries;
    range_queries.reserve(q);

    while (q--) {
        int l, r;
        cin >> l >> r;
        range_queries.emplace_back(l - 1, r);
    }

    return 0;
}
