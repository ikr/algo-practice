#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_happiness(const ll sal, const vector<pair<ll, int>> &xs) {
    const auto hi =
        accumulate(cbegin(xs), cend(xs), 0, [](const int acc, const auto ch) {
            return acc + ch.second;
        });

    // D[i][j] is the maximum remaining pounds on day i after acquiring
    // happiness amount of j. -1 pound means it's impossible to acquire
    // happiness j.
    vector<vector<ll>> D(sz(xs), vector(hi + 1, -1LL));
    D[0][0] = 0;
    if (xs[0].first == 0) D[0][xs[0].second] = 0;

    for (int i = 1; i < sz(D); ++i) {
        const auto [current_cost, current_gain] = xs[i];

        for (int h = 0; h < sz(D[i]); ++h) {
            if (D[i - 1][h] >= 0) D[i][h] = D[i - 1][h] + sal;

            if (h - current_gain >= 0 && D[i - 1][h - current_gain] >= 0 &&
                D[i - 1][h - current_gain] + sal >= current_cost) {
                D[i][h] = max(D[i][h],
                              D[i - 1][h - current_gain] + sal - current_cost);
            }
        }
    }

    int result{};
    for (int h = 0; h < sz(D.back()); ++h) {
        if (D.back()[h] >= 0) result = h;
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int m;
        cin >> m;

        ll sal;
        cin >> sal;

        vector<pair<ll, int>> xs(m);
        for (auto &[c, h] : xs) cin >> c >> h;
        cout << max_happiness(sal, xs) << '\n';
    }

    return 0;
}
