#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> ostream &operator<<(ostream &os, const optional<T> o) {
    if (!o) {
        os << "nullopt";
    } else {
        os << *o;
    }
    return os;
}

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

template <typename T> ostream &operator<<(ostream &os, const set<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int neighs(const vector<string> &grid, const pii roco) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    const auto [ro, co] = roco;

    int result{};
    result += (ro > 0 && grid[ro - 1][co] == '^');
    result += (ro < H - 1 && grid[ro + 1][co] == '^');
    result += (co > 0 && grid[ro][co - 1] == '^');
    result += (co < W - 1 && grid[ro][co + 1] == '^');
    return result;
}

set<pii> unhappy_trees(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    set<pii> result;

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (grid[ro][co] == '^' && neighs(grid, {ro, co}) < 2) {
                result.emplace(ro, co);
            }
        }
    }

    return result;
}

bool in_bounds(const vector<string> &grid, const pii roco) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    const auto [ro, co] = roco;
    return 0 <= ro && ro < H && 0 <= co && co < W;
}

optional<vector<pii>> happiness_path(const vector<string> &grid,
                                     const pii unhappy, const pii src,
                                     const set<pii> &dst) {

    map<pii, pii> pre;
    queue<pii> q;
    q.push(src);
    set<pii> visited{unhappy, src};
    optional<pii> concrete_dst;

    while (!q.empty()) {
        const auto [ro, co] = q.front();
        q.pop();

        for (const auto &adj : {pii{ro - 1, co}, pii{ro, co + 1},
                                pii{ro + 1, co}, pii{ro, co - 1}}) {
            if (!in_bounds(grid, adj)) continue;
            const auto [aro, aco] = adj;
            if (grid[aro][aco] == '#' || visited.contains(adj)) continue;

            pre[adj] = pii{ro, co};
            visited.emplace(aro, aco);

            if (dst.contains(adj)) {
                concrete_dst = adj;
                q = queue<pii>{};
                break;
            }

            q.push(adj);
        }
    }

    if (!concrete_dst) return nullopt;

    vector<pii> result{*concrete_dst};
    result.reserve(sz(pre) + 1);

    auto u = *concrete_dst;
    while (pre.contains(u)) {
        result.push_back(pre.at(u));
        u = pre.at(u);
    }

    reverse(begin(result), end(result));
    return result;
}

vector<pii> src_bridges(const vector<string> &grid, const pii roco) {
    vector<pii> result;
    const auto [ro, co] = roco;

    for (const auto &adj :
         {pii{ro - 1, co}, pii{ro, co + 1}, pii{ro + 1, co}, pii{ro, co - 1}}) {
        if (in_bounds(grid, adj) && grid[adj.first][adj.second] == '.') {
            result.push_back(adj);
        }
    }

    return result;
}

set<pii> dst_bridges(const vector<string> &grid, const pii roco) {
    set<pii> result;
    const auto [ro, co] = roco;

    for (const auto &adj :
         {pii{ro - 1, co}, pii{ro, co + 1}, pii{ro + 1, co}, pii{ro, co - 1}}) {
        if (in_bounds(grid, adj) && grid[adj.first][adj.second] != '#') {
            result.insert(adj);
        }
    }

    return result;
}

optional<vector<string>> perfect_garden(vector<string> grid) {
    auto uts = unhappy_trees(grid);
    if (uts.empty()) return grid;

    while (!uts.empty()) {
        const auto u = *cbegin(uts);
        uts.erase(cbegin(uts));

        optional<vector<pii>> path;
        const auto dst_proto = dst_bridges(grid, u);

        for (const auto &src : src_bridges(grid, u)) {
            auto dst = dst_proto;
            dst.erase(src);
            if (dst.empty()) continue;

            path = happiness_path(grid, u, src, dst);
            if (path) break;
        }

        if (!path) return nullopt;

        for (const auto &v : *path) {
            grid[v.first][v.second] = '^';
        }

        for (const auto &v : *path) {
            if (neighs(grid, v) >= 2) uts.erase(v);
        }
    }

    return grid;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int H, W;
        cin >> H >> W;

        vector<string> grid(H);
        for (auto &row : grid) {
            cin >> row;
            assert(sz(row) == W);
        }

        const auto result = perfect_garden(move(grid));
        cout << "Case #" << i << ": " << (result ? "Possible" : "Impossible")
             << '\n';

        if (result) {
            for (const auto &row : *result) {
                cout << row << '\n';
            }
        }
    }

    return 0;
}
