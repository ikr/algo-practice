#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using Coord = pair<int, int>;
using Adj = pair<int, int>;

static constexpr int Inf = 1000 * 1000 * 1000;
static constexpr int Az = 26;

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

constexpr ll code(const ll flexiwall_bits, const char cell) {
    assert(__builtin_popcountl(flexiwall_bits) <= 26);
    return (flexiwall_bits << 6) | id_of(cell);
}

constexpr ll flexiwall_bits(const ll code) { return code >> 6; }

constexpr ll cell_id(const ll code) { return code & 63LL; }
} // namespace state

vector<Adj> adjacent_state_codes(const vector<string> &grid, const Coord &roco,
                                 const int state_code) {
    assert(state::cell_id(state_code) ==
           state::id_of(grid[roco.first][roco.second]));
    vector<Adj> result;
    return result;
}

int min_total_distance_collecting_all_keys(const vector<string> &grid,
                                           const Coord &start) {
    return -1;
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) grid.push_back(line);

    const auto start = [&]() -> Coord {
        for (int ro = 0; ro < sz(grid); ++ro) {
            for (int co = 0; co < sz(grid[ro]); ++co) {
                if (grid[ro][co] == '@') return {ro, co};
            }
        }
        assert(false && "No start found");
        return {-1, -1};
    }();

    cout << min_total_distance_collecting_all_keys(grid, start) << '\n';
    return 0;
}
