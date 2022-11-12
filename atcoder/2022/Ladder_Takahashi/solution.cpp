#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pair<vector<int>, map<int, int>> encode_vertices(const vector<pii> &AB) {
    set<int> uq;
    for (const auto &[a, b] : AB) {
        uq.insert(a);
        uq.insert(b);
    }

    const vector<int> vert(cbegin(uq), cend(uq));
    map<int, int> idx;
    for (int i = 0; i < sz(vert); ++i) {
        idx[vert[i]] = i;
    }

    return {vert, idx};
}

int max_floor(const vector<pii> &AB) {
    const auto [vert, idx] = encode_vertices(AB);

    vector<vector<int>> g(sz(vert));
    for (const auto &[a, b] : AB) {
        const auto u = idx.at(a);
        const auto v = idx.at(b);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    if (!idx.count(1)) return 1;

    int result = 1;

    queue<int> q;
    q.push(idx.at(1));

    vector<bool> done(sz(vert), false);
    done[idx.at(1)] = true;

    while (!q.empty()) {
        const auto u = q.front();
        q.pop();

        for (const auto v : g[u]) {
            if (done[v]) continue;
            done[v] = true;
            result = max(result, vert[v]);
            q.push(v);
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<pii> AB(N);
    for (auto &[a, b] : AB) cin >> a >> b;

    cout << max_floor(AB) << '\n';
    return 0;
}
