#include <bits/stdc++.h>

using namespace std;

void sort_vertices_dfs(
    const unordered_multimap<int, int> &G, 
    vector<int> &ans,
    unordered_set<int> &discovered,
    const int source
) {
    const auto range = G.equal_range(source);
    for (auto it = range.first; it != range.second; ++it) {
        if (discovered.count(it->second)) continue;

        discovered.insert(it->second);
        sort_vertices_dfs(G, ans, discovered, it->second);
        ans.insert(ans.cbegin(), it->second);
    }
}

int solve(const int N, const unordered_multimap<int, int> &G) {
    vector<int> ordering;
    unordered_set<int> discovered{0};
    sort_vertices_dfs(G, ordering, discovered, 0);
    ordering.insert(ordering.cbegin(), 0);

    vector<int> dp(N + 1, 0);

    for (auto it = ordering.crbegin(); it != ordering.crend(); ++it) {
        const auto range = G.equal_range(*it);
        for (auto jt = range.first; jt != range.second; ++jt) {
            dp[*it] = max(dp[*it], dp[jt->second] + 1);
        }
    }

    return *max_element(dp.cbegin(), dp.cend()) - 1;
}

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);

    int N, M;
    cin >> N >> M;

    unordered_multimap<int, int> G;
    for (int i = 1; i <= N; ++i) {
        G.emplace(0, i);
    }

    for (int i = 0; i != M; ++i) {
        int x, y;
        cin >> x >> y;
        G.emplace(x, y);
    }

    cout << solve(N, G) << endl;

    return 0;
}
