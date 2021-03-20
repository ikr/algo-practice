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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int a, b, c, d;
    cin >> a >> b >> c >> d;
    const vi xs{a, b, c, d};

    int ans = INT_MIN;
    for (int i = 0; i < 2; ++i) {
        for (int j = 2; j < 4; ++j) {
            ans = max(ans, xs[i] - xs[j]);
        }
    }

    cout << ans << '\n';

    return 0;
}
