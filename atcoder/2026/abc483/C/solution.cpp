#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vector<int> votes(n, 0);
    vector<vector<int>> backup_indices(n, vector<int>{});

    while (m--) {
        int a, b;
        cin >> a >> b;

        votes[a - 1] += 1;
        backup_indices[a - 1].push_back(b - 1);
    }

    set<pii> pq;
    for (int i = 0; i < n; ++i) {
        pq.emplace(-votes[i], i);
    }

    for (int i0 = 0; i0 != n; ++i0) {
        const auto origninal_i0_votes = votes[i0];
        pq.erase(pii{-origninal_i0_votes, i0});

        for (const auto j : backup_indices[i0]) {
            pq.erase(pii{-votes[j], j});
            votes[j] += 1;
            pq.emplace(-votes[j], j);
        }

        cout << cbegin(pq)->second + 1 << '\n';

        for (const auto j : backup_indices[i0]) {
            pq.erase(pii{-votes[j], j});
            votes[j] -= 1;
            pq.emplace(-votes[j], j);
        }

        pq.emplace(-origninal_i0_votes, i0);
    }

    return 0;
}
