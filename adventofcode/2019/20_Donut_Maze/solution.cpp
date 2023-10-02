#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;
using Label = string;
enum class Edge { Outer, Inner };
static constexpr int Az = 'Z' - 'A' + 1;
static constexpr int LevelsUpperBound = 1000;

static const array<Coord, 4> Directions{Coord{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

struct Portal final {
    int label_code;
    Coord own_coord;
    Coord hallway_coord;
    Edge edge;
};

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

constexpr bool is_letter(const char x) { return 'A' <= x && x <= 'Z'; }

int label_code(const Label &label) {
    assert(sz(label) == 2);
    assert(is_letter(label[0]) && is_letter(label[1]));
    return (label[0] - 'A') * Az + (label[1] - 'A');
}

char cell_at(const vector<string> &grid, const Coord &roco) {
    return grid[roco.first][roco.second];
}

optional<Portal> portal_at(const vector<string> &grid, const Coord &roco) {
    const auto [ro, co] = roco;
    if (!is_letter(grid[ro][co])) return nullopt;

    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    const auto portal_edge = [&](const Coord &coord0,
                                 const Coord &coord) -> Edge {
        const auto [r, c] = min(coord0, coord);
        const auto [R, C] = max(coord0, coord);
        return r == 0 || c == 0 || R == H - 1 || C == W - 1 ? Edge::Outer
                                                            : Edge::Inner;
    };

    for (const auto &dir : Directions) {
        const auto [ro0, co0] = roco - dir;
        const auto [ro1, co1] = roco + dir;

        if (is_letter(grid[ro0][co0]) && grid[ro1][co1] == '.') {
            const auto a = cell_at(grid, min(roco, roco - dir));
            const auto b = cell_at(grid, max(roco, roco - dir));
            return Portal{label_code({a, b}),
                          {ro, co},
                          {ro1, co1},
                          portal_edge({ro0, co0}, roco)};
        }
    }

    return nullopt;
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) {
        if (!empty(line)) grid.push_back(line);
    }

    const auto [outer_loopholes, inner_loopholes, source, destination] =
        [&]() -> tuple<map<Coord, Coord>, map<Coord, Coord>, Coord, Coord> {
        map<Coord, Coord> olh;
        map<Coord, Coord> ilh;
        optional<Coord> src, dst;
        unordered_map<int, Portal> portals_by_label_code;

        for (int ro = 1; ro < sz(grid) - 1; ++ro) {
            for (int co = 1; co < sz(grid[ro]) - 1; ++co) {
                const auto p = portal_at(grid, {ro, co});
                if (!p) continue;

                if (p->label_code == 0) {
                    assert(!src && p->edge == Edge::Outer);
                    src = p->hallway_coord;
                    continue;
                }

                if (p->label_code == Az * Az - 1) {
                    assert(!dst && p->edge == Edge::Outer);
                    dst = p->hallway_coord;
                    continue;
                }

                if (portals_by_label_code.contains(p->label_code)) {
                    const auto p_ = portals_by_label_code.at(p->label_code);
                    assert(p->edge != p_.edge);

                    if (p->edge == Edge::Outer) {
                        olh.emplace(p->own_coord, p_.hallway_coord);
                        ilh.emplace(p_.own_coord, p->hallway_coord);
                    } else {
                        ilh.emplace(p->own_coord, p_.hallway_coord);
                        olh.emplace(p_.own_coord, p->hallway_coord);
                    }

                    portals_by_label_code.erase(p->label_code);
                } else {
                    portals_by_label_code.emplace(p->label_code, *p);
                }
            }
        }
        assert(empty(portals_by_label_code));

        assert(src && dst);
        return {olh, ilh, *src, *dst};
    }();

    vector<vector<vector<int>>> D(
        LevelsUpperBound,
        vector<vector<int>>(sz(grid), vector<int>(sz(grid[0]), -1)));

    D[0][source.first][source.second] = 0;
    queue<pair<int, Coord>> q;
    q.emplace(0, source);

    while (!empty(q)) {
        const auto [level0, roco0] = q.front();
        q.pop();

        for (const auto &delta : Directions) {
            auto roco = roco0 + delta;

            if (cell_at(grid, roco) == '.') {
                if (D[level0][roco.first][roco.second] != -1) continue;
                D[level0][roco.first][roco.second] =
                    D[level0][roco0.first][roco0.second] + 1;
                q.emplace(level0, roco);

            } else if (level0 && outer_loopholes.contains(roco)) {
                roco = outer_loopholes.at(roco);
                if (D[level0 - 1][roco.first][roco.second] != -1) continue;
                D[level0 - 1][roco.first][roco.second] =
                    D[level0][roco0.first][roco0.second] + 1;
                q.emplace(level0 - 1, roco);
            } else if (level0 + 1 < LevelsUpperBound &&
                       inner_loopholes.contains(roco)) {
                roco = inner_loopholes.at(roco);
                if (D[level0 + 1][roco.first][roco.second] != -1) continue;
                D[level0 + 1][roco.first][roco.second] =
                    D[level0][roco0.first][roco0.second] + 1;
                q.emplace(level0 + 1, roco);
            }
        }
    }

    cout << D[0][destination.first][destination.second] << '\n';
    return 0;
}
