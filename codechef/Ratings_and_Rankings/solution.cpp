#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

vector<pi> gather_sorted_rating_and_player_pairs(const vi &rts) {
    const int n = rts.size();
    vector<pi> ans(n);

    for (int i = 0; i < n; ++i) {
        ans[i] = pi{rts[i], i};
    }

    sort(begin(ans), end(ans), [](const pi lhs, const pi rhs) {
        return lhs.first == rhs.first ? lhs.second < rhs.second
                                      : lhs.first > rhs.first;
    });

    return ans;
}

vi gather_ranks(const vi &rts) {
    const int n = rts.size();
    const auto rt_pls = gather_sorted_rating_and_player_pairs(rts);

    vi ans(n, 0);
    for (int i = 0, rk = 1, rt = rt_pls[0].first; i < n; ++i) {
        if (rt_pls[i].first != rt) rk = i + 1;
        ans[rt_pls[i].second] = rk;
        rt = rt_pls[i].first;
    }

    return ans;
}

int first_best_row(const vvi &rows, const int co,
                   function<bool(int, int)> cmp) {
    optional<int> best;
    int ans = -1;

    for (int i = 1; i < static_cast<int>(rows.size()); ++i) {
        if (!best || cmp(*best, rows[i][co])) {
            best = rows[i][co];
            ans = i;
        }
    }

    assert(ans >= 0);
    return ans;
}

int solve(vi initial_rts, const vvi &deltas_by_player_by_month) {
    const int n = initial_rts.size();
    const int m = deltas_by_player_by_month[0].size();

    vvi rts = vvi(m + 1, initial_rts);
    vvi rks = vvi(m + 1);

    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < n; ++j) {
            rts[i][j] = rts[i - 1][j] + deltas_by_player_by_month[j][i - 1];
        }

        rks[i] = gather_ranks(rts[i]);
    }

    int ans = 0;
    for (int j = 0; j < n; ++j) {
        if (first_best_row(rts, j, less<int>{}) !=
            first_best_row(rks, j, greater<int>{})) {
            ++ans;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vi rts(n, 0);
        for (auto &rt : rts) cin >> rt;

        vvi rows(n, vi(m, 0));
        for (auto &ro : rows) {
            for (auto &d : ro) {
                cin >> d;
            }
        }

        cout << solve(rts, rows) << '\n';
    }

    return 0;
}
