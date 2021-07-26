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

int div_ceil(const int x, const int y) { return (x + y - 1) / y; }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(9) << fixed;

    int a, b, w;
    cin >> a >> b >> w;

    const int wg = w * 1000;
    const int y = wg / a;
    const int x = div_ceil(wg, b);

    if (x <= y) {
        cout << x << ' ' << y << '\n';
    } else {
        cout << "UNSATISFIABLE\n";
    }
    return 0;
}
