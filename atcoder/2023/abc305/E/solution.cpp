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

    map<int, int> guards;
    queue<pair<int, int>> q;
    set<int> guarded;
    vector<int> D(N, -1);
    for (int i = 1; i <= K; ++i) {
        int p, h;
        cin >> p >> h;
        --p;

        guards.emplace(p, h);
        q.emplace(p, p);
        guarded.insert(p);
        D[p] = 0;
    }

    while (!q.empty()) {
        const auto [u, p] = q.front();
        const auto h = guards.at(p);
        q.pop();

        for (const auto v : g[u]) {
            if (D[v] != -1) continue;
            const auto d_ = D[u] + 1;
            if (d_ > h) continue;

            D[v] = d_;
            guarded.insert(v);
            q.emplace(v, p);
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
