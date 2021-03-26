#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
constexpr int INF = 1e9;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr int capped_plus(const int a, const int b) {
    return (a == INF || b == INF) ? INF : (a + b);
}

int solve(const int x, const int y, const string &s) {
    vector<pii> cost(sz(s), {INF, INF});
    cost[0] = pii{s[0] == 'J' ? INF : 0, s[0] == 'C' ? INF : 0};

    for (int i = 1; i < sz(s); ++i) {
        if (s[i] == 'C' || s[i] == '?') {
            cost[i].first =
                min(cost[i - 1].first, capped_plus(cost[i - 1].second, y));
        }

        if (s[i] == 'J' || s[i] == '?') {
            cost[i].second =
                min(cost[i - 1].second, capped_plus(cost[i - 1].first, x));
        }
    }

    return min(cost.back().first, cost.back().second);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int x, y;
        cin >> x >> y;

        string s;
        cin >> s;

        cout << "Case #" << i << ": " << solve(x, y, s) << '\n';
    }

    return 0;
}
