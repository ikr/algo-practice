#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int find_t(const ll n) {
    assert(n >= 2);
    ll lo = 0;
    ll hi = n;

    const auto f = [](const ll t) -> ll { return t * t + t; };
    assert(f(lo) < 2 * n);
    assert(f(hi) >= 2 * n);

    while (hi - lo > 1) {
        const auto m = lo + (hi - lo) / 2;
        if (f(m) >= 2 * n) {
            hi = m;
        } else {
            lo = m;
        }
    }

    return inof(lo);
}

int max_weird_seq_length(const int k) { return 2 * (find_t(k) + 1); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int k;
        cin >> k;

        cout << max_weird_seq_length(k) << '\n';
    }

    return 0;
}
