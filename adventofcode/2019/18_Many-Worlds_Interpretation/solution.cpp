#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;

static constexpr int Inf = 1000 * 1000 * 1000;
static constexpr int Az = 26;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr bool is_key(const char x) { return 'a' <= x && x <= 'z'; }
constexpr bool is_flexiwall(const char x) { return 'A' <= x && x <= 'Z'; }

namespace state {
constexpr int code(const int flexiwall_bits, const char cell) {
    const int cell_id = cell == '@' ? Az : cell - 'a';
    return (flexiwall_bits << 5) | cell_id;
}

constexpr int flexiwall_bits(const int code) { return code >> 5; }

constexpr int cell_id(const int code) { return code & 31; }
} // namespace state

static const auto InitialWalls = []() -> unordered_set<char> {
    unordered_set<char> ans{'#'};
    for (char c = 'A'; c <= 'Z'; ++c) ans.insert(c);
    return ans;
}();

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
