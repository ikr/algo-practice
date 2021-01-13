#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = multimap<int, int>;

enum class Opt { ONLY, EXCLUDE };

struct Command final {
    Opt opt;
    int vertex;
    ll increment;
};

template <typename T> constexpr pair<T, T> flip_pair(const pair<T, T> &ab) {
    return {ab.second, ab.first};
}

Graph build_graph(const vector<pair<int, int>> &edges) {
    Graph ans;
    for (const auto [a, b] : edges) {
        ans.emplace(a, b);
        ans.emplace(b, a);
    }
    return ans;
}

vector<set<int>> as_zero_rooted_tree(const int n, const Graph &g) {
    vector<bool> visited(n, false);
    vector<set<int>> ans;

    function<void(int)> dfs;
    dfs = [&](const int u) {
        visited[u] = true;
        const auto [first, last] = g.equal_range(u);

        for (auto it = first; it != last; ++it) {
            const auto v = it->second;
            if (visited[v]) continue;

            ans[u].insert(v);
            dfs(v);
        }
    };

    dfs(0);
    return ans;
}

vector<ll> execute_commands(const int n, const vector<set<int>> &tree,
                            const vector<Command> &commands) {
    vector<ll> pro(n, 0);
    for (const auto &[opt, vertex, increment] : commands) {
        if (opt == Opt::EXCLUDE) {
            pro[0] += increment;
            pro[vertex] -= increment;
        } else {
            pro[vertex] += increment;
        }
    }

    vector<ll> ans(n, 0);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<pair<int, int>> edges(n - 1);
    for (auto &[a, b] : edges) {
        cin >> a >> b;
        --a;
        --b;
    }

    const auto tree = as_zero_rooted_tree(n, build_graph(edges));

    int q;
    cin >> q;

    vector<Command> commands(q);
    for (auto &[opt, vertex, increment] : commands) {
        int t;
        cin >> t;

        int edge_index;
        cin >> edge_index;
        --edge_index;

        cin >> increment;

        const auto [a, b] =
            t == 1 ? edges[edge_index] : flip_pair(edges[edge_index]);

        const bool a_is_parent = tree[a].count(b);
        if (a_is_parent) {
            opt = Opt::EXCLUDE;
            vertex = b;
        } else {
            opt = Opt::ONLY;
            vertex = a;
        }
    }

    for (const auto c : execute_commands(n, tree, commands)) cout << c << '\n';
    return 0;
}
