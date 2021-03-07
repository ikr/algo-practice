#include <bits/stdc++.h>
using namespace std;

int shortest_time(const vector<pair<int, int>> &ps) {
    const int n = ps.size();
    priority_queue<pair<int, int>> q_ab;
    priority_queue<pair<int, int>> q_a;
    priority_queue<pair<int, int>> q_b;

    for (int i = 0; i < n; ++i) {
        const auto [a, b] = ps[i];
        q_ab.emplace(-a - b, i);
        q_a.emplace(-a, i);
        q_b.emplace(-b, i);
    }

    const int a0 = q_a.top().second;
    q_a.pop();
    const int a1 = q_a.top().second;

    const int b0 = q_b.top().second;
    q_b.pop();
    const int b1 = q_b.top().second;

    if (a0 == b0) {
        return min({max(ps[a0].first, ps[b1].second),
                    max(ps[a1].first, ps[b0].second), -q_ab.top().first});
    }

    return min(max(ps[a0].first, ps[b0].second), -q_ab.top().first);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<pair<int, int>> ps(n);
    for (auto &[a, b] : ps) cin >> a >> b;

    cout << shortest_time(ps) << '\n';
    return 0;
}
