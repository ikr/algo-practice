#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

constexpr ll mpow(const ll base, const ll exp) {
    if (!exp) return 1;
    if (exp % 2) return (base * mpow(base, exp - 1));
    const ll q = mpow(base, exp / 2);
    return (q * q);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll n, k;
    cin >> n >> k;

    const auto ans = (n <= k) ? n : k * mpow(2, n - k);
    cout << ans << '\n';
    return 0;
}
