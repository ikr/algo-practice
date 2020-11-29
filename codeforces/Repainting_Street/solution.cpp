#include <bits/stdc++.h>
using namespace std;
static constexpr int C_MAX = 100;

vector<int> gather_freqs(const vector<int> &xs) {
    vector<int> ans(C_MAX + 1, 0);
    for (const auto x : xs) ++ans[x];
    return ans;
}

vector<int> positive_value_indices(const vector<int> &xs) {
    const int sz = xs.size();
    vector<int> ans;
    ans.reserve(C_MAX / 2);

    for (int i = 0; i < sz; ++i) {
        if (xs[i] > 0) ans.push_back(i);
    }

    return ans;
}

bool is_beautiful(const vector<int> &freqs) {
    return count_if(cbegin(freqs), cend(freqs),
                    [](const int x) { return x > 0; }) == 1;
}

vector<set<int>> gather_indices_of_others(const vector<int> &xs,
                                          const vector<int> &ys) {
    vector<set<int>> ans(ys.size());

    for (auto i = 0U; i < xs.size(); ++i) {
        for (auto j = 0U; j < ys.size(); ++j) {
            if (xs[i] != ys[j]) ans[j].insert(i);
        }
    }

    return ans;
}

int min_days(const vector<int> &xs, const int k, const set<int> &ys) {
    const int n = xs.size();
    int ans = 0;
    int i = -1;

    while (i < n) {
        const auto it = ys.lower_bound(i);
        if (it == cend(ys)) break;

        ++ans;
        i = *it + k;
    }

    return ans;
}

int min_days(const vector<int> &xs, const int k) {
    const auto freqs = gather_freqs(xs);
    if (is_beautiful(freqs)) return 0;

    int ans = 1e9;

    for (const auto &ys :
         gather_indices_of_others(xs, positive_value_indices(freqs))) {
        ans = min(ans, min_days(xs, k, ys));
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> xs(n, 0);
        for (auto &x : xs) cin >> x;
        cout << min_days(xs, k) << '\n';
    }

    return 0;
}
