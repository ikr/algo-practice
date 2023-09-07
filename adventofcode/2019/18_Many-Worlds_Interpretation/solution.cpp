#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
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

template <typename K, typename V>
ostream &operator<<(ostream &os, const unordered_map<K, V> &m) {
    os << '{';
    for (auto i = m.cbegin(); i != m.cend(); ++i) {
        if (i != m.cbegin()) os << ' ';
        os << '(' << i->first << ' ' << i->second << ')';
    }
    os << '}';
    return os;
}

static constexpr int Inf = 1000 * 1000 * 1000;
static constexpr int Az = 26;

using ll = long long;
using Coord = pair<int, int>;
using Adj = pair<ll, int>;
using CellCoords = array<Coord, Az + 4>;
using Quad = array<char, 4>;

static const vector<Coord> Deltas{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
static const vector<Coord> DiagDeltas{{-1, 1}, {-1, -1}, {1, -1}, {1, 1}};

constexpr char chof(const int x) { return static_cast<char>(x); }

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr bool is_flexiwall(const char x) { return 'A' <= x && x <= 'Z'; }
constexpr bool is_key(const char x) { return 'a' <= x && x <= 'z'; }
constexpr bool is_source(const char x) { return '0' <= x && x <= '3'; }

namespace state {
constexpr int id_of(const char cell) {
    if (is_key(cell)) return cell - 'a';
    assert(is_source(cell));
    return Az + cell - '0';
}

constexpr int quad_id_of(const Quad &quad) {
    int result{};
    for (const auto cell : quad) {
        result *= (Az + 4);
        result += id_of(cell);
    }
    return result;
}

constexpr char cell_of(const int id) {
    assert(0LL <= id && id <= Az + 3);
    return id < Az ? chof('a' + id) : chof('0' + id - Az);
}

Quad quad_of(int quad_id) {
    Quad result;
    result.fill('a');
    int i = 3;

    while (quad_id) {
        result[i--] = cell_of(quad_id % (Az + 4));
        quad_id /= (Az + 4);
    }

    return result;
}

constexpr ll code(const int flexiwall_bits, const Quad &quad) {
    assert(__builtin_popcount(flexiwall_bits) <= 26);
    return (flexiwall_bits << 20) | quad_id_of(quad);
}

constexpr int flexiwall_bits(const ll code) { return inof(code >> 20); }

constexpr int quad_id(const ll code) { return code & ((1LL << 20) - 1LL); }
} // namespace state

void quad_patch(vector<string> &grid, CellCoords &cell_coords,
                const Coord &start) {
    const auto [ro, co] = start;
    grid[ro][co] = '#';
    for (const auto &[dro, dco] : Deltas) {
        grid[ro + dro][co + dco] = '#';
    }

    for (int i = 0; i < sz(DiagDeltas); ++i) {
        const auto [dro, dco] = DiagDeltas[i];
        grid[ro + dro][co + dco] = chof('0' + i);
        cell_coords[Az + i] = {ro + dro, co + dco};
    }
}

vector<pair<Coord, int>> neighbor_cells(const vector<string> &grid,
                                        const int flexiwall_bits,
                                        const Coord &cell) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    const auto [ro0, co0] = cell;
    assert(is_source(grid[ro0][co0]) || is_key(grid[ro0][co0]));

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
                                 const ll state_code) {
    const auto quad = state::quad_of(state::quad_id(state_code));
    vector<Adj> result;

    for (int qi = 0; qi < sz(quad); ++qi) {
        const auto [ro0, co0] = cell_coords[state::id_of(quad[qi])];
        assert(ro0 != -1 && co0 != -1);

        for (const auto &rocod : neighbor_cells(
                 grid, state::flexiwall_bits(state_code), {ro0, co0})) {
            const auto [roco, d] = rocod;
            const auto [ro, co] = roco;

            const auto id = state::id_of(grid[ro][co]);
            assert((state::flexiwall_bits(state_code) & (1 << id)));

            const auto flexiwall_bits =
                state::flexiwall_bits(state_code) ^ (1 << id);

            auto quad_ = quad;
            quad_[qi] = grid[ro][co];
            result.emplace_back(state::code(flexiwall_bits, quad_), d);
        }
    }

    assert(ranges::all_of(result, [&](const auto &adj) {
        const auto [code, d] = adj;
        return __builtin_popcount(state::flexiwall_bits(code)) <
               __builtin_popcount(state::flexiwall_bits(state_code));
    }));

    return result;
}

constexpr ll initial_state_code(const CellCoords &cell_coords) {
    const auto flexiwalls_num =
        ranges::count_if(cell_coords,
                         [&](const auto &roco) {
                             return roco != Coord{-1, -1};
                         }) -
        1;
    return state::code((1 << flexiwalls_num) - 1, Quad{'0', '1', '2', '3'});
}

unordered_map<ll, vector<Adj>> weighted_graph(const vector<string> &grid,
                                              const CellCoords &cell_coords) {
    const auto u0 = initial_state_code(cell_coords);
    unordered_map<ll, vector<Adj>> g;
    const auto dfs = [&](const auto self, const ll u) -> void {
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
    cerr << g << '\n' << cell_coords << endl;
    const auto u0 = initial_state_code(cell_coords);

    unordered_map<ll, int> D;
    for (const auto &[u, adjs] : g) {
        D[u] = Inf;
        for (const auto &[v, d] : adjs) D[v] = Inf;
    }
    D[u0] = 0;

    set<pair<int, ll>> q;
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

void unit_test() {
    vector<Quad> qs{{'a', 'a', 'a', 'a'}, {'0', '1', '3', '0'},
                    {'z', '2', 'k', 'p'}, {'a', 'b', 'c', 'd'},
                    {'b', 'a', 'b', 'a'}, {'a', 'a', '0', '3'}};

    for (const auto &q : qs) {
        assert(q == state::quad_of(state::quad_id_of(q)));
    }
}

int main() {
    unit_test();

    vector<string> grid;
    for (string line; getline(cin, line);) {
        if (!empty(line)) grid.push_back(line);
    }
    assert(!empty(grid));

    CellCoords cell_coords;
    cell_coords.fill({-1, -1});

    Coord center{-1, -1};

    for (int ro = 0; ro < sz(grid); ++ro) {
        for (int co = 0; co < sz(grid[ro]); ++co) {
            const auto x = grid[ro][co];
            if (x == '#' || x == '.' || is_flexiwall(x)) continue;
            if (x == '@') {
                center = {ro, co};
                continue;
            }
            cell_coords[state::id_of(grid[ro][co])] = {ro, co};
        }
    }

    quad_patch(grid, cell_coords, center);
    for (int i = 0; i < 3; ++i) assert((cell_coords[Az + i] != Coord{-1, -1}));

    cout << min_total_distance_collecting_all_keys(grid, cell_coords) << '\n';
    return 0;
}
