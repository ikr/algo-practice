#include <bits/stdc++.h>
using namespace std;

vector<int> gather_component_marks(const int n,
                                   const unordered_multimap<int, int> &g) {
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

    return cs;
}

unordered_map<int, int> gather_counts(const vector<int> &xs) {
    unordered_map<int, int> ans;

    for (const auto x : xs) {
        ++ans[x];
    }

    return ans;
}

int max_component_size(const int n, const unordered_multimap<int, int> &g) {
    int ans = -1;

    for (const auto [k, v] : gather_counts(gather_component_marks(n, g))) {
        ans = max(ans, v);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    unordered_multimap<int, int> g;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;

        g.emplace(a - 1, b - 1);
        g.emplace(b - 1, a - 1);
    }

    cout << max_component_size(n, g) << '\n';

    return 0;
}
