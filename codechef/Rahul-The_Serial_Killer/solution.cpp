#include <bits/stdc++.h>
using namespace std;

int min_kills(const vector<int> &xs) {
    unordered_map<int, int> counts;
    for (const int x : xs) ++counts[x];

    priority_queue<pair<int, int>> q;
    for (const auto [x, freq] : counts) q.emplace(freq, x);

    int ans = 0;

    while (!q.empty()) {
        const auto [f1, x1] = q.top();
        q.pop();

        if (q.empty()) {
            ans += f1;
            break;
        }

        const auto [f2, x2] = q.top();
        q.pop();

        const int y = min(f1, f2);
        ans += y;

        if (f1 - y > 0) q.emplace(f1 - y, x1);
        if (f2 - y > 0) q.emplace(f2 - y, x2);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> xs(n, 0);
        for (auto &x : xs) cin >> x;

        cout << min_kills(xs) << '\n';
    }

    return 0;
}
