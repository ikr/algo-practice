#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vvi graph(const int n, const vector<pii> &ab) {
    vvi g(n);
    for (const auto [a, b] : ab) {
        g[a].push_back(b);
    }
    return g;
}

vi all_indegrees(const int n, const vector<pii> &ab) {
    vi ans(n, 0);
    for (const auto [_, b] : ab) {
        ++ans[b];
    }
    return ans;
}

vi properly_sorted(const vvi &g, vi indeg) {
    const auto n = sz(g);

    priority_queue<int, vi, greater<int>> q;
    for (int u = 0; u < n; ++u) {
        if (indeg[u] == 0) q.push(u);
    }

    vi ans;
    ans.reserve(n);

    while (!q.empty()) {
        const auto u = q.top();
        q.pop();

        indeg[u] = -1;

        for (const auto v : g[u]) {
            --indeg[v];

            if (indeg[v] == 0) {
                q.push(v);
            }
        }

        ans.push_back(u);
    }

    if (any_of(cbegin(indeg), cend(indeg),
               [](const int d) { return d >= 0; })) {
        return vi{};
    }

    return ans;
}

vi min_proper_perm(const int n, const vector<pii> &ab) {
    return properly_sorted(graph(n, ab), all_indegrees(n, ab));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vector<pii> ab(m);
    for (auto &[a, b] : ab) {
        cin >> a >> b;
        --a;
        --b;
    }

    sort(begin(ab), end(ab));
    ab.erase(unique(begin(ab), end(ab)), end(ab));

    const auto ans = min_proper_perm(n, ab);
    if (ans.empty()) {
        cout << "-1\n";
    } else {
        for (auto it = cbegin(ans); it != cend(ans); ++it) {
            if (it != cbegin(ans)) cout << ' ';
            cout << ((*it) + 1);
        }

        cout << '\n';
    }
    return 0;
}
