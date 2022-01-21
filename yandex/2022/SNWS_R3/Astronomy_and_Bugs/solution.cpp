#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_distortions(const vector<pii> &xys) {
    set<int> ys;
    map<int, int> yf;

    for (const auto [_, y] : xys) {
        ys.insert(y);
        ++yf[y];
    }

    map<int, int> best;
    for (const auto [x, y] : xys) {
        best[x] = max(best[x], yf[y] > 1 ? sz(ys) : (sz(ys) - 1));
    }

    ll ans{};
    for (const auto [_, a] : best) {
        ans += a;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<pii> xys;
    vector<pii> yxs;

    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        xys.emplace_back(x, y);
        yxs.emplace_back(y, x);
    }

    cout << max(max_distortions(xys), max_distortions(yxs)) << '\n';
    return 0;
}
