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

ll min_steps(const ll r, const ll xe, const ll ye) {
    const ll d_2 = xe * xe + ye * ye;
    const ll k_2 = d_2 / (r * r);
    const ll k = llof(sqrt(k_2));

    if (k * k == k_2 && d_2 == r * r * k_2) return llof(sqrt(k_2));

    if (k < 1) return 2;

    return k + 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int r, xe, ye;
    cin >> r >> xe >> ye;
    cout << min_steps(r, xe, ye) << '\n';

    return 0;
}
