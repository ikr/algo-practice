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

optional<vector<pii>> happiness_path(const vector<string> &grid,
                                     const set<pii> &uts, const pii src) {
    assert(uts.contains(src));
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    const auto in_bounds = [&](const pii roco) -> bool {
        const auto [ro, co] = roco;
        return 0 <= ro && ro < H && 0 <= co && co < W;
    };

    const auto adjacent_unhappy = [&](const pii roco) -> optional<pii> {
        const auto [ro, co] = roco;

        for (const auto &adj : {pii{ro - 1, co}, pii{ro, co + 1},
                                pii{ro + 1, co}, pii{ro, co - 1}}) {
            if (in_bounds(adj) && uts.contains(adj)) return adj;
        }

        return nullopt;
    };

    map<pii, pii> pre;
    queue<pii> q;
    set<pii> visited{src};

    {
        const auto [ro, co] = src;
        vector<pii> to_enq;

        for (const auto &adj : {pii{ro - 1, co}, pii{ro, co + 1},
                                pii{ro + 1, co}, pii{ro, co - 1}}) {
            if (in_bounds(adj) && grid[adj.first][adj.second] == '.') {
                to_enq.push_back(adj);
            }
        }

        if (to_enq.empty()) return nullopt;
        for (const auto &u : to_enq) {
            q.push(u);
            visited.insert(u);
            pre[u] = src;
        }

        cerr << "src:" << src << " to_enq:" << to_enq << endl;
    }

    optional<pii> dst;

    while (!q.empty()) {
        const auto [ro, co] = q.front();
        q.pop();

        for (const auto &adj : {pii{ro - 1, co}, pii{ro, co + 1},
                                pii{ro + 1, co}, pii{ro, co - 1}}) {
            if (!in_bounds(adj)) continue;
            const auto [aro, aco] = adj;
            if (grid[aro][aco] == '#') continue;

            if (grid[ro][co] == '.') {
                const auto unh = adjacent_unhappy(adj);
                if (unh) {
                    pre[*unh] = adj;
                    dst = *unh;
                    q = queue<pii>{};
                    pre[adj] = pii{ro, co};
                    break;
                }
            }

            if (visited.count(adj)) continue;

            pre[adj] = pii{ro, co};
            visited.emplace(aro, aco);
        }
    }

    if (!dst) return nullopt;

    vector<pii> result{*dst};
    result.reserve(sz(pre) + 1);

    auto u = *dst;
    while (pre.count(u)) {
        result.push_back(pre.at(u));
        u = pre.at(u);
    }

    reverse(begin(result), end(result));
    return result;
}

optional<vector<string>> perfect_garden(vector<string> grid) {
    auto uts = unhappy_trees(grid);
    cerr << "uts:" << uts << endl;
    if (uts.empty()) return grid;

    while (!uts.empty()) {
        const auto path = happiness_path(grid, uts, *cbegin(uts));
        if (!path) return nullopt;

        cerr << "path:" << path << endl;

        const auto src = path->front();
        const auto dst = path->back();
        assert(grid[src.first][src.second] == '^');
        assert(grid[dst.first][dst.second] == '^');

        for (int i = 1; i < sz(*path) - 1; ++i) {
            const auto [ro, co] = (*path)[i];
            grid[ro][co] = '^';
        }

        for (const auto &u : *path) {
            if (neighs(grid, u) >= 2) {
                uts.erase(u);
            }
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
