#include <bits/stdc++.h>
using namespace std;

int min_kills(const vector<int> &xs) {
    unordered_map<int, int> counts;
    for (const int x : xs) ++counts[x];

    priority_queue<int> q;
    for (const auto [x, freq] : counts) q.push(freq);

    int ans = 0;

    while (!q.empty()) {
        const auto f1 = q.top();
        q.pop();

        if (q.empty()) {
            ans += f1;
            break;
        }

        const auto f2 = q.top();
        q.pop();

        ++ans;

        if (f1 - 1) q.push(f1 - 1);
        if (f2 - 1) q.push(f2 - 1);
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
