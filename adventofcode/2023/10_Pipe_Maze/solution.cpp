#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

template <typename T>
constexpr pair<T, T> operator-(const pair<T, T> a, const pair<T, T> b) {
    return {a.first - b.first, a.second - b.second};
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr pair North{-1, 0};
static constexpr pair East{0, 1};
static constexpr pair South{1, 0};
static constexpr pair West{0, -1};
static const vector<Coord> Deltas{North, East, South, West};

static const unordered_map<char, vector<Coord>> ConnectionDeltas{
    {'|', {{-1, 0}, {1, 0}}}, {'-', {{0, -1}, {0, 1}}},
    {'L', {{-1, 0}, {0, 1}}}, {'J', {{-1, 0}, {0, -1}}},
    {'7', {{1, 0}, {0, -1}}}, {'F', {{1, 0}, {0, 1}}}};

int direction(const Coord delta) {
    const auto i = inof(ranges::find(Deltas, delta) - Deltas.begin());
    assert(i < sz(Deltas));
    return i;
}

Coord start_coord(const vector<string> &grid) {
    for (int ro = 0; ro < sz(grid); ++ro) {
        for (int co = 0; co < sz(grid[ro]); ++co) {
            if (grid[ro][co] == 'S') return {ro, co};
        }
    }

    assert(false && "Start missing");
    return {-1, -1};
}

void add_to(set<Coord> &dst, const vector<Coord> &src) {
    dst.insert(cbegin(src), cend(src));
}

char resolve_angle(const Coord d1, const Coord d2) {
    const map<pair<Coord, Coord>, char> m{
        {{South, West}, 'J'}, {{South, East}, 'L'}, {{North, West}, '7'},
        {{North, East}, 'F'}, {{East, North}, 'J'}, {{East, South}, '7'},
        {{West, North}, 'L'}, {{West, South}, 'F'}};
    return m.at({d1, d2});
}

int main() {
    vector<string> grid;
    for (string s; getline(cin, s);) grid.emplace_back(std::move(s));

    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    const auto in_bounds = [H, W](const Coord u) {
        const auto [ro, co] = u;
        return 0 <= ro && ro < H && 0 <= co && co < W;
    };

    const auto cell = [&](const Coord u) {
        return in_bounds(u) ? grid[u.first][u.second] : ' ';
    };

    const auto is_connected = [&](const Coord u, const Coord delta) -> bool {
        const auto c = cell(u + delta);
        if (!ConnectionDeltas.contains(c)) return false;
        for (const auto &d : ConnectionDeltas.at(c)) {
            if (u + delta + d == u) return true;
        }
        return false;
    };

    const auto adjacent = [&](const Coord u) -> vector<Coord> {
        const auto c = cell(u);
        if (c == 'S') {
            vector<Coord> result;
            for (const auto &d : Deltas) {
                if (is_connected(u, d)) result.push_back(u + d);
            }
            return result;
        }

        if (!ConnectionDeltas.contains(c)) return {};
        vector<Coord> result;
        for (const auto &d : ConnectionDeltas.at(c)) {
            const auto v = u + d;
            if (in_bounds(v)) result.push_back(v);
        }
        return result;
    };

    const auto S = start_coord(grid);
    vector<vector<int>> dist(H, vector<int>(W, -1));
    dist[S.first][S.second] = 0;

    const auto recur = [&](const auto self, const Coord u) -> void {
        assert(dist[u.first][u.second] != -1);
        for (const auto &v : adjacent(u)) {
            if (dist[v.first][v.second] != -1) continue;
            dist[v.first][v.second] = dist[u.first][u.second] + 1;
            self(self, v);
        }
    };
    recur(recur, S);

    map<int, Coord> path_idx;
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (dist[ro][co] != -1) path_idx[dist[ro][co]] = {ro, co};
        }
    }
    vector<Coord> path;
    for (const auto &[_, u] : path_idx) path.push_back(u);
    assert(path[0] == S);
    grid[S.first][S.second] =
        resolve_angle(path[0] - path.back(), path[1] - path[0]);
    path.push_back(S);

    const auto neighs = [&](const Coord u,
                            const vector<Coord> &ds) -> vector<Coord> {
        vector<Coord> result;
        for (const auto &d : ds) {
            const auto v = u + d;

            if (in_bounds(v) && dist[v.first][v.second] == -1) {
                result.push_back(u + d);
            }
        }
        return result;
    };

    set<Coord> lefts;
    set<Coord> rights;

    for (int i = 1; i < sz(path); ++i) {
        const auto [ro, co] = path[i];
        const auto c = grid[ro][co];

        switch (direction(path[i] - path[i - 1])) {
        case 0: // North
            if (c == '|') {
                add_to(lefts, neighs(path[i], {West}));
                add_to(rights, neighs(path[i], {East}));
            } else if (c == 'F') {
                add_to(lefts, neighs(path[i], {West, North, West + North}));
                add_to(rights, neighs(path[i], {East + South}));
            } else if (c == '7') {
                add_to(lefts, neighs(path[i], {West + South}));
                add_to(rights, neighs(path[i], {East, North, East + North}));
            } else {
                assert(false && "Can't go North");
            }
            break;
        case 1: // East
            if (c == '-') {
                add_to(lefts, neighs(path[i], {North}));
                add_to(rights, neighs(path[i], {South}));
            } else if (c == 'J') {
                add_to(lefts, neighs(path[i], {North + West}));
                add_to(rights, neighs(path[i], {South, East, South + East}));
            } else if (c == '7') {
                add_to(lefts, neighs(path[i], {North, East, North + East}));
                add_to(rights, neighs(path[i], {South + West}));
            } else {
                assert(false && "Can't go East");
            }
            break;
        case 2: // South
            if (c == '|') {
                add_to(lefts, neighs(path[i], {East}));
                add_to(rights, neighs(path[i], {West}));
            } else if (c == 'J') {
                add_to(lefts, neighs(path[i], {East, South, South + East}));
                add_to(rights, neighs(path[i], {North + West}));
            } else if (c == 'L') {
                add_to(lefts, neighs(path[i], {North + East}));
                add_to(rights, neighs(path[i], {West, South, South + West}));
            } else {
                assert(false && "Can't go South");
            }
            break;
        default: // West
            if (c == '-') {
                add_to(lefts, neighs(path[i], {South}));
                add_to(rights, neighs(path[i], {North}));
            } else if (c == 'F') {
                add_to(lefts, neighs(path[i], {South + East}));
                add_to(rights, neighs(path[i], {North, West, North + West}));
            } else if (c == 'L') {
                add_to(lefts, neighs(path[i], {South, West, South + West}));
                add_to(rights, neighs(path[i], {North + East}));
            } else {
                assert(false && "Can't go Worth");
            }
            break;
        }
    }

    for (const auto &src : {lefts, rights}) {
        auto visited = src;

        const auto flood_fill = [&](const auto self, const Coord u) -> void {
            for (const auto &d : Deltas) {
                const auto v = u + d;
                if (!in_bounds(v)) continue;
                if (dist[v.first][v.second] != -1 || visited.contains(v)) {
                    continue;
                }
                visited.insert(v);
                self(self, v);
            }
        };
        for (const auto &u : src) flood_fill(flood_fill, u);
        cout << sz(visited) << '\n';
    }
    return 0;
}
