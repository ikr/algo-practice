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
    set<int> guarded;

    for (int i = 1; i <= K; ++i) {
        int p, h;
        cin >> p >> h;
        --p;

        q.emplace(h, p);
        guarded.insert(p);
    }

    while (!q.empty()) {
        const auto [h, u] = q.top();
        assert(h);
        q.pop();

        for (const auto v : g[u]) {
            if (guarded.count(v)) continue;
            guarded.insert(v);
            if (h - 1) q.emplace(h - 1, v);
        }
    }

    cout << size(guarded) << '\n';
    for (auto i = guarded.cbegin(); i != guarded.cend(); ++i) {
        if (i != guarded.cbegin()) cout << ' ';
        cout << (*i) + 1;
    }
    cout << '\n';
    return 0;
}
