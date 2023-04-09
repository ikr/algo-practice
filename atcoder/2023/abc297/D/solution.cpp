#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll ops_count(const ll a, const ll b) {
    if (a == b) return 0;

    ll ans = b / a;
    ll r = b % a;
    return ans + (r ? ops_count(r, a) : 0);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll a, b;
    cin >> a >> b;
    if (a > b) swap(a, b);

    const auto ans = ops_count(a, b);
    cout << (ans ? ans - 1 : 0) << '\n';
    return 0;
}
