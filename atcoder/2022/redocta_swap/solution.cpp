#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

map<string, int> all_vertices() {
    map<string, int> result;
    int i{};
    string xs{"atcoder"};
    sort(begin(xs), end(xs));

    do {
        result[xs] = i++;
    } while (next_permutation(begin(xs), end(xs)));

    return result;
}

vector<int> adjacent(const map<string, int> &idx, const string &u) {
    vector<int> result;

    for (int i = 1; i < sz(u); ++i) {
        auto v = u;
        swap(v[i - 1], v[i]);
        result.push_back(idx.at(v));
    }

    return result;
}

int min_ops(const string &xs) {
    if (xs == "atcoder") return 0;
    const auto idx = all_vertices();

    const auto n = sz(idx);
    vector<string> vs(n);
    for (const auto &[k, v] : idx) {
        vs[v] = k;
    }
    const auto T = idx.at("atcoder");

    vector<vector<int>> g(n);
    for (int u = 0; u < n; ++u) {
        g[u] = adjacent(idx, vs[u]);
    }

    vector<int> D(n, -1);
    D[idx.at(xs)] = 0;

    queue<int> q;
    q.push(idx.at(xs));

    while (!q.empty()) {
        const auto u = q.front();
        q.pop();

        for (const auto v : g[u]) {
            if (D[v] >= 0) continue;
            if (v == T) return D[u] + 1;

            D[v] = D[u] + 1;
            q.push(v);
        }
    }

    return D[T];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    cin >> xs;

    cout << min_ops(xs) << '\n';
    return 0;
}
