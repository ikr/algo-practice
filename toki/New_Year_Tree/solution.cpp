#include <bits/stdc++.h>
using namespace std;
using Graph = multimap<int, int>;
using Tree = vector<set<int>>;

Graph build_graph(const vector<pair<int, int>> &edges) {
    Graph ans;
    for (const auto [a, b] : edges) {
        ans.emplace(a, b);
        ans.emplace(b, a);
    }
    return ans;
}

Tree as_zero_rooted_tree(const int n, const Graph &g) {
    vector<bool> visited(n, false);
    Tree ans(n);

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

map<int, int> gather_parents(const Tree &t) {
    map<int, int> ans{{0, -1}};

    function<void(int)> dfs;
    dfs = [&](const int u) {
        for (const int v : t.at(u)) {
            ans.emplace(v, u);
            dfs(v);
        }
    };

    dfs(0);
    return ans;
}

int xor_up_to_root(const map<int, int> &ps, const vector<int> states,
                   const int u) {
    int v = u;
    vector<int> path;
    while (v != -1) {
        path.push_back(v);
        v = ps.at(v);
    }

    reverse(begin(path), end(path));
    int ans = 0;
    for (const int w : path) {
        ans ^= states[w];
    }
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

    const auto t = as_zero_rooted_tree(n, build_graph(edges));
    const auto ps = gather_parents(t);
    vector<int> states(n, 0);

    int q;
    cin >> q;
    while (q--) {
        int opcode;
        cin >> opcode;

        if (opcode == 1) {
            int u, x;
            cin >> u >> x;
            --u;
            states[u] ^= x;
        } else {
            assert(opcode == 2);
            int u;
            cin >> u;
            --u;
            cout << xor_up_to_root(ps, states, u) << '\n';
        }
    }

    return 0;
}
