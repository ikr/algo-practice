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

ll opposed_to_c(const ll a, const ll b, const ll c) {
    const auto half_arc = b - a - 1;
    const auto period = half_arc * 2 + 2;

    const auto opposite = [&](const ll x) {
        return (x + half_arc + 1) % period;
    };

    if (opposite(a) != b || opposite(b) != a || c >= period) return -1;
    return opposite(c);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        ll a, b, c;
        cin >> a >> b >> c;

        --a;
        --b;
        --c;

        const auto ans = opposed_to_c(min(a, b), max(a, b), c);
        cout << (ans == -1 ? -1 : ans + 1) << '\n';
    }

    return 0;
}
