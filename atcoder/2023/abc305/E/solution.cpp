#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

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
    for (int i = 1; i <= K; ++i) {
        int p, h;
        cin >> p >> h;
        --p;

        guards.emplace(p, h);
    }

    set<int> guarded;

    for (const auto &[p, h] : guards) {
        guarded.insert(p);
        map<int, int> D;
        D.emplace(p, 0);

        queue<int> q;
        q.push(p);

        while (!q.empty()) {
            const auto u = q.front();
            q.pop();

            for (const auto v : g[u]) {
                if (D.count(v)) continue;
                const auto d_ = D[u] + 1;
                D.emplace(v, d_);
                assert(d_ <= h);
                guarded.insert(v);
                if (d_ < h) q.push(v);
            }
        }
    }

    cout << sz(guarded) << '\n';
    for (auto i = guarded.cbegin(); i != guarded.cend(); ++i) {
        if (i != guarded.cbegin()) cout << ' ';
        cout << (*i) + 1;
    }
    cout << '\n';
    return 0;
}
