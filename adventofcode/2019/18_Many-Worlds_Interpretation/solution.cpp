#include <bits/stdc++.h>
using namespace std;

static constexpr int Inf = 1000 * 1000 * 1000;
static constexpr int Az = 26;

using ll = long long;
using Coord = pair<int, int>;
using Adj = pair<int, int>;
using CellCoords = array<Coord, 2 * Az + 1>;

constexpr char chof(const int x) { return static_cast<char>(x); }

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr bool is_flexiwall(const char x) { return 'A' <= x && x <= 'Z'; }
constexpr bool is_key(const char x) { return 'a' <= x && x <= 'z'; }

namespace state {
constexpr ll id_of(const char cell) {
    if (is_flexiwall(cell)) return cell - 'A';
    if (is_key(cell)) return Az + cell - 'a';

    assert(cell == '@');
    return 2 * Az;
}

constexpr char cell_of(const ll id) {
    assert(0LL <= id && id <= 2 * Az);
    if (id < Az) return chof('A' + inof(id));
    if (id < 2 * Az) return chof('a' + inof(id) - Az);
    return '@';
}

constexpr ll code(const ll flexiwall_bits, const char cell) {
    assert(__builtin_popcountl(flexiwall_bits) <= 26);
    return (flexiwall_bits << 6) | id_of(cell);
}

constexpr ll flexiwall_bits(const ll code) { return code >> 6; }

constexpr ll cell_id(const ll code) { return code & 63LL; }
} // namespace state

vector<Adj> adjacent_state_codes(const vector<string> &grid,
                                 const CellCoords &cell_coords,
                                 const int state_code) {
    const auto [ro0, co0] = cell_coords[state::cell_id(state_code)];
    assert(ro0 != -1 && co0 != -1);
    vector<Adj> result;
    return result;
}

int min_total_distance_collecting_all_keys(const vector<string> &grid,
                                           const CellCoords &cell_coords) {
    return -1;
}

void unit_test() {
    {
        const auto c = state::code((1LL << 26) - 1LL, '@');
        assert(state::flexiwall_bits(c) == 0b11111111111111111111111111LL);
        assert(state::cell_of(state::cell_id(c)) == '@');
    }
    {
        const auto c = state::code(1, 'G');
        assert(state::flexiwall_bits(c) == 1LL);
        assert(state::cell_of(state::cell_id(c)) == 'G');
    }
    {
        const auto c = state::code(8, 'b');
        assert(state::flexiwall_bits(c) == 8LL);
        assert(state::cell_of(state::cell_id(c)) == 'b');
    }
}

int main() {
    unit_test();
    vector<string> grid;
    for (string line; getline(cin, line);) grid.push_back(line);

    CellCoords cell_coords;
    cell_coords.fill({-1, -1});

    for (int ro = 0; ro < sz(grid); ++ro) {
        for (int co = 0; co < sz(grid[ro]); ++co) {
            const auto x = grid[ro][co];
            if (x == '#' || x == '.') continue;
            cell_coords[state::id_of(grid[ro][co])] = {ro, co};
        }
    }

    assert(cell_coords[state::id_of('@')] != (Coord{-1, -1}));
    cout << min_total_distance_collecting_all_keys(grid, cell_coords) << '\n';
    return 0;
}
