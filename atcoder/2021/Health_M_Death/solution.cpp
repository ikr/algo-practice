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
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(9) << fixed;

    int m, h;
    cin >> m >> h;

    const bool ans = (h % m == 0);
    cout << (ans ? "Yes\n" : "No\n");

    return 0;
}
