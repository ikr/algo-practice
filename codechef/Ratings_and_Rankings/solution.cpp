#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

vector<pi> gather_sorted_rating_and_player_pairs(const vector<int> &rts) {
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

vector<int> gather_ranks(const vector<int> &rts) {
    const int n = rts.size();
    const auto rt_pls = gather_sorted_rating_and_player_pairs(rts);

    vector<int> ans(n, 0);
    for (int i = 0, rk = 1, rt = rt_pls[0].first; i < n; ++i) {
        if (rt_pls[i].first != rt) rk = i + 1;
        ans[rt_pls[i].second] = rk;
        rt = rt_pls[i].first;
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
