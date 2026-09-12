#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, s;
    cin >> n >> s;
    --s;

    ll l;
    cin >> l;

    vector<ll> aa(n - 1, 0LL);
    for (auto &a : aa) {
        cin >> a;
    }

    vector<ll> dist(n, LLONG_MAX);
    dist[s] = 0LL;

    for (int i = s - 1; i >= 0; --i) {
        dist[i] = dist[i + 1] + aa[i];
    }

    for (int i = s + 1; i <= n - 1; ++i) {
        dist[i] = dist[i - 1] + aa[i - 1];
    }

    cerr << dist << '\n';

    return 0;
}
