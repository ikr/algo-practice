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

int min_ops(const ll x, const ll y) {
    if (gcd(x, y) > 1LL) return 0;
    if (x % 2 == 0 || y % 2 == 0) return 1;
    if (gcd(x + 1, y) > 1LL) return 1;
    if (gcd(x, y + 1) > 1LL) return 1;
    return 2;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        ll x, y;
        cin >> x >> y;
        cout << min_ops(x, y) << '\n';
    }

    return 0;
}
