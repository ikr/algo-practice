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

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

ll solve(const ll A, const ll B, const ll C, const ll D) {
    if (D * C - B == 0LL) return -1;

    if (doof(A) / doof(D * C - B) < 0.0) return -1;
    return div_ceil(abs(A), abs(D * C - B));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int A, B, C, D;
    cin >> A >> B >> C >> D;

    cout << solve(A, B, C, D) << '\n';

    return 0;
}
