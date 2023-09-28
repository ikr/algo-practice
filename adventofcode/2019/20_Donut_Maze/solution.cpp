#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;
using Label = array<char, 2>;
static constexpr int Az = 'Z' - 'A' + 1;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr bool is_letter(const char x) { return 'A' <= x && x <= 'Z'; }

constexpr int label_code(const Label &label) {
    assert(is_letter(label[0]) && is_letter(label[1]));
    return (label[0] - 'A') * Az + (label[1] - 'A');
}

optional<pair<Label, Coord>> portal_at(const vector<string> &grid,
                                       const Coord &roco) {
    return nullopt;
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) grid.push_back(line);

    return 0;
}
