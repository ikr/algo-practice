#include <bits/stdc++.h>
using namespace std;

int count_componernts(const int n, const unordered_multimap<int, int> &g) {
    vector<int> cs(n, -1);
    int curr = -1;

    function<void(int)> dfs;
    dfs = [&dfs, &g, &cs, &curr](const int x) {
        cs[x] = curr;

        const auto [first, last] = g.equal_range(x);
        for (auto it = first; it != last; ++it) {
            if (cs[it->second] >= 0) continue;
            dfs(it->second);
        }
    };

    for (int i = 0; i < n; ++i) {
        if (cs[i] == -1) {
            ++curr;
            dfs(i);
        }
    }

    return curr + 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        unordered_multimap<int, int> g(n);

        for (int i = 1; i <= n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            g.emplace(u - 1, v - 1);
        }

        cout << (count_componernts(n, g) - 1) << '\n';
    }

    return 0;
}
