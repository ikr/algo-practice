#include <bits/stdc++.h>
#include <climits>
using namespace std;

vector<int> gather_ranks(const vector<int> &rts) {
    const int n = rts.size();
    multimap<int, int> players_by_rt;

    for (int i = 0; i < n; ++i) {
        players_by_rt.emplace(rts[i], i);
    }

    int prev_rt = INT_MIN;
    int curr_rk = 0;

    vector<int> ans(n, -1);

    for (auto it = crbegin(players_by_rt); it != crend(players_by_rt); ++it) {
        const auto [rt, pl] = *it;

        if (prev_rt == INT_MIN) {
            curr_rk = 1;
        } else if (prev_rt != rt) {
            curr_rk = count_if(cbegin(ans), cend(ans),
                               [](int rt) { return rt != -1; }) +
                      1;
        }
        ans[pl] = curr_rk;
        prev_rt = rt;
    }

    return ans;
}

int solve(vector<int> rts, const vector<vector<int>> &rows) {
    const int n = rts.size();
    const int m = rows[0].size();
    vector<int> rts_hi = rts;
    vector<int> rks_hi = gather_ranks(rts);

    unordered_set<int> ans_players;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            const int d = rows[j][i];

            rts[j] += d;
            rts_hi[j] = max(rts_hi[j], rts[j]);
        }

        const auto rks = gather_ranks(rts);
        for (int j = 0; j < n; ++j) {
            rks_hi[j] = min(rks_hi[j], rks[j]);
        }

        for (int j = 0; j < n; ++j) {
            if ((rts_hi[j] == rts[j] && rks_hi[j] != rks[j]) ||
                (rks_hi[j] == rks[j] && rts_hi[j] != rts[j])) {
                ans_players.insert(i);
            }
        }
    }

    return ans_players.size();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<int> rts(n, 0);
        for (auto &rt : rts) cin >> rt;

        vector<vector<int>> rows(n, vector<int>(m, 0));
        for (auto &ro : rows) {
            for (auto &d : ro) {
                cin >> d;
            }
        }

        cout << solve(rts, rows) << '\n';
    }

    return 0;
}
