#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Project final {
    const int start;
    const int finish;
    const int reward;

    Project(const int s, const int f, const int r)
        : start{s}, finish{f}, reward{r} {}
};

map<int, int> gather_milestone_indices(const vector<Project> &projects) {
    map<int, int> ans;

    for (const auto &p : projects) {
        ans[p.start] = 0;
        ans[p.finish + 1] = 0;
    }

    for (auto [i, it] = pair{0, ans.begin()}; it != ans.end(); ++it, ++i) {
        it->second = i;
    }

    return ans;
}

ll max_total_reward(const vector<Project> &projects) {
    const auto milestone_indices = gather_milestone_indices(projects);
    const int sz = milestone_indices.size();

    vector<vector<Project>> finished_by_milestone_index(sz);
    for (const auto &p : projects) {
        finished_by_milestone_index[milestone_indices.at(p.finish + 1)]
            .push_back(p);
    }

    // dp[i] — optimal total reward before the milestone i
    vector<ll> dp(sz, 0);

    for (int i = 1; i != sz; ++i) {
        dp[i] = dp[i - 1];

        for (const auto &p : finished_by_milestone_index.at(i)) {
            dp[i] = max(dp[i], dp[milestone_indices.at(p.start)] + p.reward);
        }
    }

    return dp.back();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz;
    cin >> sz;
    vector<Project> projects;
    while (sz--) {
        int a, b, p;
        cin >> a >> b >> p;
        projects.emplace_back(a, b, p);
    }

    cout << max_total_reward(projects) << '\n';
    return 0;
}
