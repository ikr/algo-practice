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

bool can_win(const vi &xs) {
    int spans = 1;
    int curr = xs[0];

    for (int i = 1; i < sz(xs); ++i) {
        const int x = xs[i];
        if (x == curr) continue;

        ++spans;
        curr = x;
    }

    return spans <= 4;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;

    vi xs(n);
    for (auto &x : xs) cin >> x;

    cout << (can_win(xs) ? "YES\n" : "NO\n");
    return 0;
}
