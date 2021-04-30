#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr ll M = 1e9 + 7;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;

    vll xs(n);
    for (auto &x : xs) cin >> x;

    ll total =
        accumulate(cbegin(xs), cend(xs), 0LL,
                   [](const ll agg, const ll x) { return (agg + x + M) % M; });

    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int x;
        cin >> x;

        total *= 2LL;
        total %= M;

        cout << total << '\n';
    }

    return 0;
}
