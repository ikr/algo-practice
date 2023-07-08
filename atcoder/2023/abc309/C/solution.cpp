#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    ll K;
    cin >> N >> K;

    map<ll, ll> delta_by_day;
    for (int i = 1; i <= N; ++i) {
        ll a, b;
        cin >> a >> b;

        delta_by_day[1] += b;
        delta_by_day[1 + a] -= b;
    }

    ll ans = 1;
    ll cur{};

    for (const auto [t, delta] : delta_by_day) {
        cur += delta;
        if (cur <= K) {
            ans = t;
            break;
        }
    }

    cout << ans << '\n';
    return 0;
}
