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

using Coord = pair<int, int>;
using Edge = pair<int, int>;

enum class Dir { Up, Right, Down, Left };
static constexpr array Delta{Coord{-1, 0}, Coord{0, 1}, Coord{1, 0},
                             Coord{0, -1}};

constexpr int Inf = 1'000'000'000;

constexpr Dir dir_of(const Coord delta) {
    const int i = static_cast<int>(ranges::find(Delta, delta) - cbegin(Delta));
    assert(0 <= 1 && i < ssize(Delta));
    return static_cast<Dir>(i);
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
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
    return {a.first + b.first, a.second + b.second};
}

template <typename T>
constexpr pair<T, T> scaled_by(const pair<T, T> ab, const T k) {
    return {k * ab.first, k * ab.second};
}

constexpr Coord coord_of(const int W, const int id) {
    if (id == -1) return {-1, -1};
    const int r = id / W;
    const int c = id % W;
    return {r, c};
}

constexpr Coord make_unit(Coord rc) {
    if (rc.first) rc.first = 1;
    if (rc.second) rc.second = 1;
    return rc;
}

constexpr bool same_direction_twice(const Coord delta1, const Coord delta2) {
    return make_unit(delta1) == make_unit(delta2);
}

int min_heat_loss_dijkstra(const int W, const vector<vector<Edge>> &graph) {
    const auto n = sz(graph);

    vector<int> D(n, Inf);
    D[0] = 0;

    vector<int> P(n, -1);

    set<pair<int, int>> q;
    q.emplace(0, 0);

    while (!empty(q)) {
        int v = q.begin()->second;
        q.erase(q.begin());

        for (const auto &[to, len] : graph[v]) {
            const auto da = coord_of(W, v) - coord_of(W, P[v]);
            const auto db = coord_of(W, to) - coord_of(W, v);
            cerr << "da:" << da << " db:" << db
                 << " sdt:" << same_direction_twice(da, db) << endl;

            if (D[v] + len < D[to] && !same_direction_twice(da, db)) {
                q.erase({D[to], to});
                D[to] = D[v] + len;
                P[to] = v;
                q.emplace(D[to], to);
            }
        }
    }

    return D.back();
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

    const auto adjacent_coord_losses =
        [&](const Coord rc) -> vector<pair<Coord, int>> {
        vector<pair<Coord, int>> result;

        for (const auto &delta : Delta) {
            int current_heat_loss{};

            for (int steps = 1; steps <= 3; ++steps) {
                const auto shift = scaled_by(delta, steps);
                if (!in_bounds(rc + shift)) break;
                current_heat_loss += heat_loss_at(rc + shift);
                result.emplace_back(rc + shift, current_heat_loss);
            }
        }

        return result;
    };

    const auto id_of = [&](const Coord rc) -> int {
        const auto [r, c] = rc;
        return r * W + c;
    };

    vector<vector<Edge>> graph(H * W);
    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            const auto rc = Coord{r, c};
            for (const auto &[rc_, heat_loss] : adjacent_coord_losses(rc)) {
                graph[id_of(rc)].emplace_back(id_of(rc_), heat_loss);
            }
        }
    }

    cout << min_heat_loss_dijkstra(W, graph) << '\n';
    return 0;
}
