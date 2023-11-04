#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<int> A(M);
    for (auto &a : A) {
        cin >> a;
        --a;
    }

    vector<int> B(M);
    for (auto &b : B) {
        cin >> b;
        --b;
    }

    vector<vector<int>> adj(N);
    for (int i = 0; i < M; ++i) {
        adj[A[i]].push_back(B[i]);
        adj[B[i]].push_back(A[i]);
    }

    vector<int> side(N, -1);
    bool is_bipartite = true;
    queue<int> q;
    for (int u0 = 0; u0 < N; ++u0) {
        if (side[u0] == -1) {
            q.push(u0);
            side[u0] = 0;
            while (!q.empty()) {
                const auto v = q.front();
                q.pop();
                for (const auto u : adj[v]) {
                    if (side[u] == -1) {
                        side[u] = side[v] ^ 1;
                        q.push(u);
                    } else {
                        is_bipartite &= (side[u] != side[v]);
                    }
                }
            }
        }
    }

    cout << (is_bipartite ? "Yes" : "No") << '\n';
    return 0;
}
