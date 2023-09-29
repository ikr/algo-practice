#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;
using Label = string;
static constexpr int Az = 'Z' - 'A' + 1;

struct Portal final {
    int label_code;
    Coord own_coord;
    Coord hallway_coord;
};

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr bool is_letter(const char x) { return 'A' <= x && x <= 'Z'; }

constexpr int label_code(const Label &label) {
    assert(sz(label) == 2);
    assert(is_letter(label[0]) && is_letter(label[1]));
    return (label[0] - 'A') * Az + (label[1] - 'A');
}

optional<Portal> portal_at(const vector<string> &grid, const Coord &roco) {
    const auto [ro, co] = roco;
    if (!is_letter(grid[ro][co])) return nullopt;

    if (is_letter(grid[ro - 1][co])) {
        assert(grid[ro + 1][co] == '.');
        return Portal{label_code({grid[ro - 1][co], grid[ro][co]}),
                      {ro, co},
                      {ro + 1, co}};
    }

    if (is_letter(grid[ro + 1][co])) {
        assert(grid[ro - 1][co] == '.');
        return Portal{label_code({grid[ro][co], grid[ro + 1][co]}),
                      {ro, co},
                      {ro - 1, co}};
    }

    // wip

    return nullopt;
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) {
        if (!empty(line)) grid.push_back(line);
    }

    return 0;
}
