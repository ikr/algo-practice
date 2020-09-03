#include <bits/stdc++.h>
using namespace std;
using Ints = vector<int>;
using Graph = unordered_multimap<int, int>;

Graph gather_children(const Ints &parent) {
    const int N = parent.size() - 1;
    Graph ans;
    for (int i = 2; i <= N; ++i) ans.emplace(parent[i], i);
    return ans;
}

Ints gather_skip_sources_counts(const int N, const Graph &children,
                                const int step) {
    Ints ans(N + 1, 0);

    Ints path;
    function<void(int)> dfs;

    dfs = [&dfs, &children, &step, &path, &ans](const int x) {
        path.push_back(x);
        const auto range = children.equal_range(x);

        for (auto it = range.first; it != range.second; ++it) {
            dfs(it->second);
        }

        ++ans[x];
        const int sz = path.size();
        const int target = sz - 1 - step;
        if (target >= 0) ans[path[target]] += ans[x];

        path.pop_back();
    };

    dfs(1);
    return ans;
}

double solve(const Ints &parent, const int step_a, const int step_b) {
    const int N = parent.size() - 1;
    const auto children = gather_children(parent);
    const auto src_a = gather_skip_sources_counts(N, children, step_a);
    const auto src_b = gather_skip_sources_counts(N, children, step_b);

    double ans = 0;
    for (int i = 0; i <= N; ++i) {
        const double p_a = src_a[i];
        const double p_b = src_b[i];

        ans += (p_a + p_b) / N - (p_a * p_b) / N / N;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(6) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, A, B;
        cin >> N >> A >> B;

        Ints parent(N + 1, 0);
        for (int i = 2; i <= N; ++i) cin >> parent[i];

        cout << "Case #" << i << ": " << solve(parent, A, B) << '\n';
    }

    return 0;
}
