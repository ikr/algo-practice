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

ostream &operator<<(ostream &os, const vector<string> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

template <typename K, typename V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << '{';
    for (auto i = m.cbegin(); i != m.cend(); ++i) {
        if (i != m.cbegin()) os << ' ';
        os << '(' << i->first << ' ' << i->second << ')';
    }
    os << '}';
    return os;
}

using Coord = pair<int, int>;
enum class Dir { Up, Right, Down, Left };
using Vert = pair<Coord, Dir>;
using Edge = pair<Vert, int>;

ostream &operator<<(ostream &os, const Dir &d) {
    const auto a = [&]() -> string {
        switch (d) {
        case Dir::Up:
            return "U";
        case Dir::Right:
            return "R";
        case Dir::Down:
            return "D";
        default:
            assert(d == Dir::Left);
            return "L";
        }
    }();
    cout << a;
    return os;
}

ostream &operator<<(ostream &os, const Vert &u) {
    os << '(' << u.first << ' ' << u.second << ')';
    return os;
}

static constexpr array Delta{Coord{-1, 0}, Coord{0, 1}, Coord{1, 0},
                             Coord{0, -1}};

constexpr int Inf = 1'000'000'000;

constexpr Dir dir_of(const Coord delta) {
    const int i = static_cast<int>(ranges::find(Delta, delta) - cbegin(Delta));
    assert(0 <= 1 && i < ssize(Delta));
    return static_cast<Dir>(i);
}

constexpr Dir opposite(const Dir dir) {
    switch (dir) {
    case Dir::Up:
        return Dir::Down;
    case Dir::Right:
        return Dir::Left;
    case Dir::Down:
        return Dir::Up;
    default:
        assert(dir == Dir::Left);
        return Dir::Right;
    }
}

constexpr Coord delta_of(const Dir dir) {
    const int i = static_cast<int>(dir);
    assert(0 <= i && i < ssize(Delta));
    return Delta[i];
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

template <typename T>
constexpr pair<T, T> operator-(const pair<T, T> a, const pair<T, T> b) {
    return {a.first - b.first, a.second - b.second};
}

template <typename T>
constexpr pair<T, T> scaled_by(const pair<T, T> ab, const T k) {
    return {k * ab.first, k * ab.second};
}

int min_heat_loss_dijkstra(const Coord dim,
                           const map<Vert, vector<Edge>> &graph) {
    const auto [H, W] = dim;
    map<Vert, int> D;
    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            for (const auto dir : {Dir::Up, Dir::Right, Dir::Down, Dir::Left}) {
                const auto u = Vert{{r, c}, dir};
                D[u] = Inf;
            }
        }
    }

    D[Vert{{0, 0}, Dir::Right}] = 0;
    D[Vert{{0, 0}, Dir::Down}] = 0;

    set<pair<int, Vert>> q;
    q.emplace(0, Vert{{0, 0}, Dir::Right});
    q.emplace(0, Vert{{0, 0}, Dir::Down});

    while (!empty(q)) {
        const auto v = cbegin(q)->second;
        q.erase(cbegin(q));

        for (const auto &[to, len] : graph.at(v)) {
            if (D.at(v) + len < D.at(to)) {
                q.erase({D.at(to), to});
                D[to] = D.at(v) + len;
                q.emplace(D.at(to), to);
            }
        }
    }

    return min(D.at(Vert{{H - 1, W - 1}, Dir::Down}),
               D.at(Vert{{H - 1, W - 1}, Dir::Right}));
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) {
        grid.push_back(std::move(line));
    }

    const int H = sz(grid);
    const int W = sz(grid[0]);

    const auto in_bounds = [&](const Coord rc) -> bool {
        const auto [r, c] = rc;
        return 0 <= r && r < H && 0 <= c && c < W;
    };

    const auto heat_loss_at = [&](const Coord rc) -> int {
        assert(in_bounds(rc));
        const auto [r, c] = rc;
        return grid[r][c] - '0';
    };

    const auto adjacent_coord_losses = [&](const Vert v) -> vector<Edge> {
        vector<Edge> result;
        const auto [rc0, dir0] = v;

        for (const auto &delta : Delta) {
            const auto dir = dir_of(delta);
            if (dir0 == dir || dir0 == opposite(dir)) continue;
            int current_heat_loss{};

            for (int steps = 1; steps <= 3; ++steps) {
                const auto shift = scaled_by(delta, steps);
                if (!in_bounds(rc0 + shift)) break;
                current_heat_loss += heat_loss_at(rc0 + shift);
                result.emplace_back(Vert{rc0 + shift, dir}, current_heat_loss);
            }
        }

        return result;
    };

    map<Vert, vector<Edge>> graph;
    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            for (const auto dir : {Dir::Up, Dir::Right, Dir::Down, Dir::Left}) {
                const auto u = Vert{{r, c}, dir};
                graph[u] = adjacent_coord_losses(u);
            }
        }
    }

    cout << min_heat_loss_dijkstra({H, W}, graph) << '\n';
    return 0;
}
