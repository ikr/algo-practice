#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

double square(const int x) { return x * x; }

double eucl(const pii p1, const pii p2) {
    const auto [x1, y1] = p1;
    const auto [x2, y2] = p2;
    return sqrt(square(x1 - x2) + square(y1 - y2));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(7) << fixed;

    int n;
    cin >> n;
    vector<pii> ps(n);

    for (auto &[x, y] : ps) {
        cin >> x >> y;
    }

    double ans = 0;

    for (int i = 0; i < sz(ps) - 1; ++i) {
        for (int j = i + 1; j < sz(ps); ++j) {
            ans = max(ans, eucl(ps[i], ps[j]));
        }
    }

    cout << ans << '\n';
    return 0;
}
