#include <bits/stdc++.h>

using namespace std;

int dfs(vector<int> &memo, const unordered_multimap<int, int> &G, const int source) {
    const auto range = G.equal_range(source); 

    for (auto it = range.first; it != range.second; ++it) {
        memo[source] = max(memo[source], 1 + dfs(memo, G, it->second));
    }

    return memo[source];
}

int solve(const int N, const unordered_multimap<int, int> &G) {
    vector<int> memo(N + 1, 0);

    for (int i = 1; i <= N; ++i) {
        dfs(memo, G, i);
    }

    return *max_element(memo.cbegin(), memo.cend());
}

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);

    int N, M;
    cin >> N >> M;

    unordered_multimap<int, int> G;
    for (int i = 0; i != M; ++i) {
        int x, y;
        cin >> x >> y;
        G.emplace(x, y);
    }

    cout << solve(N, G) << endl;

    return 0;
}
