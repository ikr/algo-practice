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

int manhattan(const int xa, const int ya, const int xb, const int yb) {
    return abs(xa - xb) + abs(ya - yb);
}

bool is_between(const pii ab, const int x) {
    const auto [a, b] = ab;
    return min(a, b) <= x && x <= max(a, b);
}

int min_d(const int xa, const int ya, const int xb, const int yb, const int xf,
          const int yf) {
    if ((xa == xb && xf == xa && is_between({ya, yb}, yf)) ||
        (ya == yb && yf == ya && is_between({xa, xb}, xf))) {
        return manhattan(xa, ya, xb, yb) + 2;
    }

    return manhattan(xa, ya, xb, yb);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int xa, ya, xb, yb, xf, yf;
        cin >> xa >> ya >> xb >> yb >> xf >> yf;
        cout << min_d(xa, ya, xb, yb, xf, yf) << '\n';
    }

    return 0;
}
