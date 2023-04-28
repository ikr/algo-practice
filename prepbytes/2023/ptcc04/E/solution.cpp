#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/UnionFind.h
namespace kactl {
struct UF {
    vector<int> e;
    UF(int n) : e(n, -1) {}
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b);
        e[a] += e[b];
        e[b] = a;
        return true;
    }
};
} // namespace kactl

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

bool confirm_vertices_connected(const vector<vector<int>> &g,
                                const vector<int> &xs) {
    const auto n = sz(g);
    kactl::UF cs(n);
    for (int u = 0; u < n; ++u) {
        for (const auto v : g[u]) cs.join(u, v);
    }

    const auto c0 = cs.find(xs[0]);
    return all_of(xbegin(xs), xend(xs),
                  [&](const int x) { return cs.find(x) == c0; });
}

vector<int> distances_from(const vector<vector<int>> &g, const int u0) {
    const auto n = sz(g);
    vector<int> D(n, -1);
    D[u0] = 0;
    queue<int> q;
    q.push(u0);

    while (!q.empty()) {
        const auto u = q.front();
        q.pop();

        for (const auto v : g[u]) {
            if (D[v] != -1) continue;
            D[v] = D[u] + 1;
            q.push(v);
        }
    }

    return D;
}

vector<vector<int>> distance_matrix(const vector<vector<int>> &g,
                                    const vector<int> &xs) {
    const auto k = sz(xs);
    const set<int> xss(xbegin(xs), xend(xs));
    vector<vector<int>> ans(k, vector<int>(k, -1));

    for (int i = 0; i < k; ++i) {
        const auto D = distances_from(g, xs[i]);

        for (int j = 0; j < k; ++j) {
            ans[i][j] = ans[j][i] = D[xs[j]];
        }
    }

    return ans;
}

int solve_on(const vector<vector<int>> &D) {
    const int n = sz(D);
    int ans{};

    for (int i = 1; i < n; ++i) {
        ans += D[i - 1][i];
    }

    return ans + 1;
}

int min_path_length(const vector<vector<int>> &g, const vector<int> &xs) {
    if (!confirm_vertices_connected(g, xs)) return -1;
    return solve_on(distance_matrix(g, xs));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> g(N);
    for (int i = 1; i <= M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    int K;
    cin >> K;

    vector<int> xs(K);
    for (auto &x : xs) {
        cin >> x;
        --x;
    }

    cerr << min_path_length(g, xs) << '\n';
    return 0;
}
