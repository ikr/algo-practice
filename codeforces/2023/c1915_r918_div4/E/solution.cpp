#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const vector<ll> &xs) {
    const auto n = sz(xs);
    if (n == 1) return false;

    int i = 0;
    ll ev = xs[0];
    int j = 1;
    ll od = xs[1];

    for (;;) {
        if (ev == od) return true;
        if (j + 1 >= n) return false;

        auto ev_ = ev;
        auto od_ = od;
        if ((j + 1) % 2) {
            od_ += xs[j + 1];
        } else {
            ev_ += xs[j + 1];
        }

        if (abs(xs[j] - xs[j + 1]) <= abs(ev_ - od_)) {
            i = j;
            j = j + 1;
            ev = i % 2 ? xs[j] : xs[i];
            od = i % 2 ? xs[i] : xs[j];
        } else {
            ++j;
            ev = ev_;
            od = od_;
        }
    }

    assert(false && "/o\\");
    return false;
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
