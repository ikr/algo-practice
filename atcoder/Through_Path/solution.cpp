#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = multimap<int, int>;

enum class Dir { UP, DOWN };

struct Command final {
    Dir dir;
    int edge_index;
    ll increment;
};

Graph build_graph(const vector<pair<int, int>> &edges) {
    Graph ans;
    for (const auto [a, b] : edges) {
        ans.emplace(a, b);
        ans.emplace(b, a);
    }
    return ans;
}

Graph as_zero_rooted_tree(const int n, const Graph &g) {
    vector<bool> visited(n, false);
    Graph ans;

    function<void(int)> dfs;
    dfs = [&](const int u) {
        visited[u] = true;
        const auto [first, last] = g.equal_range(u);

        for (auto it = first; it != last; ++it) {
            const auto v = it->second;
            if (visited[v]) continue;

            ans.emplace(u, v);
            dfs(v);
        }
    };

    dfs(0);
    return ans;
}

vector<ll> execute_commands(const vector<pair<int, int>> &edges,
                            const vector<Command> &commands) {
    const int n = edges.size() + 1;
    const auto tree = as_zero_rooted_tree(n, build_graph(edges));

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

    int q;
    cin >> q;

    vector<Command> commands(q);
    for (auto &[dir, edge_index, increment] : commands) {
        int t;
        cin >> t;
        dir = (t == 1) ? Dir::UP : Dir::DOWN;

        cin >> edge_index;
        --edge_index;

        cin >> increment;
    }

    for (const auto c : execute_commands(edges, commands)) cout << c << '\n';
    return 0;
}
