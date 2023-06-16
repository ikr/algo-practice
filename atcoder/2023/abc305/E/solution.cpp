#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M, K;
    cin >> N >> M >> K;

    vector<vector<int>> g(N);
    for (int i = 1; i <= M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    priority_queue<pair<int, int>> q;
    vector<int> potential(N, -1);

    for (int i = 1; i <= K; ++i) {
        int p, h;
        cin >> p >> h;
        --p;

        q.emplace(h, p);
        potential[p] = h;
    }

    while (!q.empty()) {
        const auto [h, u] = q.top();
        assert(h > 0);
        q.pop();

        for (const auto v : g[u]) {
            if (h - 1 <= potential[v]) continue;
            potential[v] = h - 1;
            if (h - 1 > 0) q.emplace(h - 1, v);
        }
    }

    vector<long long> guarded;
    for (auto i = cbegin(potential); i != cend(potential); ++i) {
        if (*i >= 0) guarded.push_back(i - cbegin(potential));
    }

    cout << size(guarded) << '\n';
    for (auto i = cbegin(guarded); i != cend(guarded); ++i) {
        if (i != cbegin(guarded)) cout << ' ';
        cout << (*i) + 1;
    }
    cout << '\n';
    return 0;
}
