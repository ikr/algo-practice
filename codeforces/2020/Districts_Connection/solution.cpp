#include <bits/stdc++.h>
using namespace std;

bool has_single_unique_element(const vector<int> &xs) {
    return unordered_set<int>(cbegin(xs), cend(xs)).size() == 1U;
}

vector<pair<int, int>> roads(const vector<int> &xs) {
    if (has_single_unique_element(xs)) return {};

    const int n = xs.size();
    const int chosen_gang = xs[0];
    queue<int> chosen;
    queue<int> others;

    for (int i = 0; i < n; ++i) {
        if (xs[i] == chosen_gang) {
            chosen.push(i);
        } else {
            others.push(i);
        }
    }

    vector<pair<int, int>> ans;

    while (others.size() > 1) {
        ans.emplace_back(chosen.front(), others.front());
        others.pop();
    }

    while (!chosen.empty()) {
        ans.emplace_back(chosen.front(), others.front());
        chosen.pop();
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n{0};
        cin >> n;
        vector<int> xs(n, 0);
        for (auto &x : xs) cin >> x;

        const auto ans = roads(xs);
        if (ans.empty()) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            for (const auto [a, b] : ans) cout << a + 1 << ' ' << b + 1 << '\n';
        }
    }

    return 0;
}
