#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

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

using pii = pair<int, int>;

static constexpr int INF = 1000 * 1000 * 1000;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int H, W, T;
    cin >> H >> W >> T;

    vector<string> grid(H);
    for (auto &row : grid) {
        cin >> row;
        assert(sz(row) == W);
    }

    pii start{}, goal{};
    vector<pii> candies;

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            switch (grid[ro][co]) {
            case 'S':
                start = pii{ro, co};
                break;
            case 'G':
                goal = pii{ro, co};
                break;
            case 'o':
                candies.emplace_back(ro, co);
            }
        }
    }

    const auto n = sz(candies) + 2;
    vector<vector<pii>> g(n);

    const auto vertex_roco = [&](const int v) -> pii {
        if (v == n - 2) return start;
        if (v == n - 1) return goal;
        assert(0 <= v && v < sz(candies));
        return candies[v];
    };

    const auto vertices_by_roco = [&]() {
        map<pii, int> result;
        for (int v = 0; v < n; ++v) result[vertex_roco(v)] = v;
        return result;
    }();

    const auto trace_from = [&](const int u0) -> void {
        vector<vector<int>> D(H, vector(W, INF));
        const auto [ro0, co0] = vertex_roco(u0);
        D[ro0][co0] = 0;

        queue<pii> q;
        q.push(vertex_roco(u0));

        while (!q.empty()) {
            const auto [ro, co] = q.front();
            q.pop();

            if (ro > 0 && grid[ro - 1][co] != '#' && D[ro - 1][co] == INF) {
                D[ro - 1][co] = D[ro][co] + 1;
                q.emplace(ro - 1, co);
            }

            if (co < W - 1 && grid[ro][co + 1] != '#' && D[ro][co + 1] == INF) {
                D[ro][co + 1] = D[ro][co] + 1;
                q.emplace(ro, co + 1);
            }

            if (ro < H - 1 && grid[ro + 1][co] != '#' && D[ro + 1][co] == INF) {
                D[ro + 1][co] = D[ro][co] + 1;
                q.emplace(ro + 1, co);
            }

            if (co > 0 && grid[ro][co - 1] != '#' && D[ro][co - 1] == INF) {
                D[ro][co - 1] = D[ro][co] + 1;
                q.emplace(ro, co - 1);
            }
        }

        for (int ro = 0; ro < H; ++ro) {
            for (int co = 0; co < W; ++co) {
                if (D[ro][co] == INF) continue;
                const auto it = vertices_by_roco.find({ro, co});
                if (it == cend(vertices_by_roco)) continue;

                g[u0].emplace_back(it->second, D[ro][co]);
            }
        }
    };

    for (int u0 = 0; u0 < n; ++u0) trace_from(u0);
    cerr << g << endl;
    return 0;
}
