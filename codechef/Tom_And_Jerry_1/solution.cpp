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

int manhattan(const pii ab, const pii cd) {
    return abs(ab.first - cd.first) + abs(ab.second - cd.second);
}

bool is_possible(const int a, const int b, const int c, const int d,
                 const int k) {
    const auto m = manhattan({a, b}, {c, d});
    if (k < m) return false;
    if (k == m) return true;
    return (k - m) % 2 == 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int a, b, c, d, k;
        cin >> a >> b >> c >> d >> k;

        cout << (is_possible(a, b, c, d, k) ? "YES\n" : "NO\n");
    }

    return 0;
}
