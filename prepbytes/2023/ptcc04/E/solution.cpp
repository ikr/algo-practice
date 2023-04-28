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

vector<vector<int>>
pad_distance_matrix_with_origin_city(const vector<vector<int>> &D0) {
    const auto k = sz(D0);
    vector<vector<int>> D(k + 1, vector<int>(k + 1, 0));
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            D[i + 1][j + 1] = D0[i][j];
        }
    }
    return D;
}

static constexpr int INF = 1000000000;

vector<int> pop_one_more_bit(const int n, const int x) {
    vector<int> ans;
    ans.reserve(n);

    for (int i = 1; i < n; ++i) {
        const int mask = 1 << i;
        if (x & mask) continue;
        ans.push_back(x | mask);
    }

    return ans;
}

set<int> pop_one_more_bit(const int n, const set<int> &xs) {
    set<int> ans;

    for (const auto x : xs) {
        const auto ys = pop_one_more_bit(n, x);
        ans.insert(cbegin(ys), cend(ys));
    }

    return ans;
}

int gather_tsp_answer(const vector<vector<int>> &D,
                      const vector<vector<int>> &dp) {
    const int n = sz(dp);
    const int complete_set = (1 << n) - 1;
    int ans = INF;

    for (int i = 1; i < n; ++i) {
        ans = min(ans, dp[i][complete_set] + D[i][0]);
    }

    return ans;
}

int solve_tsp(const vector<vector<int>> &D0) {
    const auto D = pad_distance_matrix_with_origin_city(D0);
    const int n = sz(D);

    // minimal distance from point 0
    // [to point i] [over j bits-defined subset of points]
    vector<vector<int>> dp(n, vector<int>(1 << n, INF));

    vector<set<int>> subsets_by_point(n);

    for (int i = 1; i < n; ++i) {
        const int mask = 1 | (1 << i);
        subsets_by_point[i].insert(mask);
        dp[i][mask] = D[0][i];
    }

    for (int k = 3; k <= n; ++k) {
        for (auto &ss : subsets_by_point) ss = pop_one_more_bit(n, ss);

        for (int i = 1; i < n; ++i) {
            for (const auto &ss : subsets_by_point[i]) {
                for (int b = 1; b < n; ++b) {
                    const int mask = 1 << i;
                    if ((mask & ss) && b != i) {
                        dp[i][ss] = min(dp[i][ss], dp[b][ss & ~mask] + D[b][i]);
                    }
                }
            }
        }
    }

    return gather_tsp_answer(D, dp) + 1;
}

int min_path_length(const vector<vector<int>> &g, const vector<int> &xs) {
    if (!confirm_vertices_connected(g, xs)) return -1;
    return solve_tsp(distance_matrix(g, xs));
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
