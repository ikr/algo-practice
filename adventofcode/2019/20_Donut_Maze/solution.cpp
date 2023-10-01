#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;
using Label = string;
static constexpr int Az = 'Z' - 'A' + 1;

static const array<Coord, 4> Directions{Coord{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

struct Portal final {
    int label_code;
    Coord own_coord;
    Coord hallway_coord;
};

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

ostream &operator<<(ostream &dest, const Portal &p) {
    dest << "P(L:" << p.label_code << " O:" << p.own_coord
         << " H:" << p.hallway_coord << ')';
    return dest;
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

    for (const auto &dir : Directions) {
        const auto [ro0, co0] = roco - dir;
        const auto [ro1, co1] = roco + dir;

        if (is_letter(grid[ro0][co0]) && grid[ro1][co1] == '.') {
            const auto a = cell_at(grid, min(roco, roco - dir));
            const auto b = cell_at(grid, max(roco, roco - dir));
            return Portal{label_code({a, b}), {ro, co}, {ro1, co1}};
        }
    }

    return nullopt;
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) {
        if (!empty(line)) grid.push_back(line);
    }

    vector<Portal> portals;
    for (int ro = 1; ro < sz(grid) - 1; ++ro) {
        for (int co = 1; co < sz(grid[ro]) - 1; ++co) {
            if (const auto p = portal_at(grid, {ro, co}); p) {
                portals.push_back(*p);
            }
        }
    }
    cerr << portals << endl;
    return 0;
}
