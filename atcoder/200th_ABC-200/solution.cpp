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

ll solution(const ll n, const ll k) {
    ll x = n;

    for (ll i = 1; i <= k; ++i) {
        if (x % 200LL == 0LL) {
            x /= 200LL;
        } else {
            x *= 1000LL;
            x += 200;
        }
    }

    return x;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    ll n, k;
    cin >> n >> k;

    cout << solution(n, k) << '\n';

    return 0;
}
