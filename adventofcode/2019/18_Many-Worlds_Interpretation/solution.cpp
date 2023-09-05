#include <bits/stdc++.h>
using namespace std;

static constexpr int Inf = 1000 * 1000 * 1000;
static constexpr int Az = 26;

using Coord = pair<int, int>;
using Adj = pair<int, int>;
using CellCoords = array<Coord, Az + 1>;

static const vector<Coord> Deltas{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
static const vector<Coord> DiagDeltas{{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};

constexpr char chof(const int x) { return static_cast<char>(x); }

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr bool is_flexiwall(const char x) { return 'A' <= x && x <= 'Z'; }
constexpr bool is_key(const char x) { return 'a' <= x && x <= 'z'; }

namespace state {
constexpr int id_of(const char cell) {
    if (is_key(cell)) return cell - 'a';
    assert(cell == '@');
    return Az;
}

constexpr char cell_of(const int id) {
    assert(0LL <= id && id <= Az);
    if (id != Az) return chof('a' + id);
    return '@';
}

constexpr int code(const int flexiwall_bits, const char cell) {
    assert(__builtin_popcount(flexiwall_bits) <= 26);
    return (flexiwall_bits << 5) | id_of(cell);
}

constexpr int flexiwall_bits(const int code) { return code >> 5; }

constexpr int cell_id(const int code) { return code & 31LL; }
} // namespace state

void quad_patch(vector<string> &grid, const Coord &start) {
    const auto [ro, co] = start;
    grid[ro][co] = '#';
    for (const auto &[dro, dco] : Deltas) {
        grid[ro + dro][co + dco] = '#';
    }

    for (const auto &[dro, dco] : DiagDeltas) {
        grid[ro + dro][co + dco] = '@';
    }
}

vector<pair<Coord, int>> neighbor_cells(const vector<string> &grid,
                                        const int flexiwall_bits,
                                        const Coord &cell) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    const auto [ro0, co0] = cell;
    assert(grid[ro0][co0] == '@' || is_key(grid[ro0][co0]));

    const auto is_wall = [&](const int ro, const int co) -> bool {
        const auto x = grid[ro][co];
        if (x == '#') return true;
        return is_flexiwall(x) && (flexiwall_bits & (1 << (x - 'A')));
    };

    const auto is_new_key = [&](const int ro, const int co) -> bool {
        const auto x = grid[ro][co];
        return is_key(x) && (flexiwall_bits & (1 << (x - 'a')));
    };

    vector<pair<Coord, int>> result;

    vector<vector<int>> D(H, vector(W, Inf));
    D[ro0][co0] = 0;

    queue<Coord> q;
    q.push(cell);

    while (!empty(q)) {
        const auto [ro, co] = q.front();
        q.pop();

        for (const auto &[dro, dco] : Deltas) {
            const auto [ro_, co_] = Coord{ro + dro, co + dco};
            if (D[ro_][co_] != Inf || is_wall(ro_, co_)) continue;

            D[ro_][co_] = D[ro][co] + 1;

            if (is_new_key(ro_, co_)) {
                result.emplace_back(Coord{ro_, co_}, D[ro_][co_]);
            } else {
                q.emplace(ro_, co_);
            }
        }
    }

    return result;
}

vector<Adj> adjacent_state_codes(const vector<string> &grid,
                                 const CellCoords &cell_coords,
                                 const int state_code) {
    const auto [ro0, co0] = cell_coords[state::cell_id(state_code)];
    assert(ro0 != -1 && co0 != -1);

    vector<Adj> result;
    ranges::transform(
        neighbor_cells(grid, state::flexiwall_bits(state_code), {ro0, co0}),
        back_inserter(result), [&](const auto &rocod) -> Adj {
            const auto [roco, d] = rocod;
            const auto [ro, co] = roco;

            const auto id = state::id_of(grid[ro][co]);
            assert((state::flexiwall_bits(state_code) & (1 << id)));
            const auto flexiwall_bits =
                state::flexiwall_bits(state_code) ^ (1 << id);

            return {state::code(flexiwall_bits, grid[ro][co]), d};
        });

    assert(ranges::all_of(result, [&](const auto &adj) {
        const auto [code, d] = adj;
        return __builtin_popcount(state::flexiwall_bits(code)) <
               __builtin_popcount(state::flexiwall_bits(state_code));
    }));

    return result;
}

constexpr int initial_state_code(const CellCoords &cell_coords) {
    const auto flexiwalls_num =
        ranges::count_if(cell_coords,
                         [&](const auto &roco) {
                             return roco != Coord{-1, -1};
                         }) -
        1;
    return state::code((1 << flexiwalls_num) - 1, '@');
}

unordered_map<int, vector<Adj>> weighted_graph(const vector<string> &grid,
                                               const CellCoords &cell_coords) {
    const auto u0 = initial_state_code(cell_coords);
    unordered_map<int, vector<Adj>> g;
    const auto dfs = [&](const auto self, const int u) -> void {
        if (g.contains(u)) return;
        for (const auto &[v, d] : adjacent_state_codes(grid, cell_coords, u)) {
            g[u].emplace_back(v, d);
            self(self, v);
        }
    };

    dfs(dfs, u0);
    for (const auto &[u, adjs] : g) {
        for (const auto &[v, d] : adjs) g[v];
    }
    return g;
}

int min_total_distance_collecting_all_keys(const vector<string> &grid,
                                           const CellCoords &cell_coords) {
    const auto g = weighted_graph(grid, cell_coords);
    const auto u0 = initial_state_code(cell_coords);

    unordered_map<int, int> D;
    for (const auto &[u, adjs] : g) {
        D[u] = Inf;
        for (const auto &[v, d] : adjs) D[v] = Inf;
    }
    D[u0] = 0;

    set<pair<int, int>> q;
    q.emplace(0, u0);

    while (!empty(q)) {
        const auto [du, u] = *cbegin(q);
        q.erase(cbegin(q));

        for (const auto &[v, d] : g.at(u)) {
            if (D[v] > du + d) {
                q.erase({D[v], v});
                D[v] = du + d;
                q.emplace(D[v], v);
            }
        }
    }

    auto result{Inf};
    for (const auto &[v, d] : D) {
        if (state::flexiwall_bits(v) == 0) result = min(result, d);
    }
    return result;
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) {
        if (!empty(line)) grid.push_back(line);
    }
    assert(!empty(grid));

    CellCoords cell_coords;
    cell_coords.fill({-1, -1});

    for (int ro = 0; ro < sz(grid); ++ro) {
        for (int co = 0; co < sz(grid[ro]); ++co) {
            const auto x = grid[ro][co];
            if (x == '#' || x == '.' || is_flexiwall(x)) continue;
            cell_coords[state::id_of(grid[ro][co])] = {ro, co};
        }
    }

    assert(cell_coords[state::id_of('@')] != (Coord{-1, -1}));
    cout << min_total_distance_collecting_all_keys(grid, cell_coords) << '\n';
    return 0;
}
