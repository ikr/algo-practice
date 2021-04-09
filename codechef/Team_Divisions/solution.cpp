#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vll = vector<ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr ll M = 998244353LL;

constexpr ll pow_mod(const ll base, const ll exp) {
    if (!exp) return 1;
    if (exp % 2) return (base * pow_mod(base, exp - 1)) % M;
    const ll q = pow_mod(base, exp / 2);
    return (q * q) % M;
}

int divisions_num(const vector<pii> &xys) { return -1; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<pii> xys(n);
        for (auto &[x, y] : xys) cin >> x >> y;

        sort(begin(xys), end(xys));
        cout << divisions_num(xys) << '\n';
    }

    return 0;
}
