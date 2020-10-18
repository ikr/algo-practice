#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Coord = tuple<int, int, int>;

static constexpr ll INF = 1e18;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

ll dist(const Coord &x, const Coord &y) {
    const auto [a, b, c] = x;
    const auto [p, q, r] = y;
    return abs(llof(p) - a) + abs(llof(q) - b) + max(0LL, llof(r) - c);
}

vector<int> pop_one_more_bit(const int n, const int x) {
    vector<int> ans;
    ans.reserve(n);

    for (int i = 1; i < n; ++i) {
        const int mask = 1 << i;
        if (x & mask) continue;
        ans.push_back(x | mask);
    }

    return ans;
}

set<int> pop_one_more_bit(const int n, const set<int> &xs) {
    set<int> ans;

    for (const auto x : xs) {
        const auto ys = pop_one_more_bit(n, x);
        ans.insert(cbegin(ys), cend(ys));
    }

    return ans;
}

ll gather_tsp_answer(const vector<Coord> &ps, const vector<vector<ll>> &dp) {
    const int n = dp.size();
    const int complete_set = (1 << n) - 1;
    ll ans = INF;

    for (int i = 1; i < n; ++i) {
        ans = min(ans, dp[i][complete_set] + dist(ps[i], ps[0]));
    }

    return ans;
}

ll solve_tsp(const vector<Coord> &ps) {
    const int n = ps.size();

    // minimal distance from point 0
    // [to point i] [over j bits-defined subset of points]
    vector<vector<ll>> dp(n, vector<ll>(1 << n, INF));

    vector<set<int>> subsets_by_point(n);

    for (int i = 1; i < n; ++i) {
        const int mask = 1 | (1 << i);
        subsets_by_point[i].insert(mask);
        dp[i][mask] = dist(ps[0], ps[i]);
    }

    for (int k = 3; k <= n; ++k) {
        for (auto &ss : subsets_by_point) ss = pop_one_more_bit(n, ss);

        for (int i = 1; i < n; ++i) {
            for (const auto &ss : subsets_by_point[i]) {
                for (int b = 1; b < n; ++b) {
                    const int mask = 1 << b;
                    if ((mask & ss) && b != i) {
                        dp[i][ss] = min(dp[i][ss],
                                        dp[b][ss & ~mask] + dist(ps[b], ps[i]));
                    }
                }
            }
        }
    }

    return gather_tsp_answer(ps, dp);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<Coord> ps(n);
    for (auto &[x, y, z] : ps) cin >> x >> y >> z;

    cout << solve_tsp(ps) << '\n';
    return 0;
}
