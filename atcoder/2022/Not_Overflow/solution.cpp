#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll x;
    cin >> x;

    const ll edge = (1LL << 31LL);
    const auto ans = (-edge <= x) && (x < edge);
    cout << (ans ? "Yes" : "No") << '\n';
    return 0;
}
