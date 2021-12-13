#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Coord = pair<int, int>;

enum class Dir { HORZ, VERT };

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

optional<Coord> fold_one_horz(const Coord coord, const int v) {
    const auto [x, y] = coord;
    if (x == v) return nullopt;
    if (x < v) return coord;

    const auto dx = x - v;
    return pair{v - dx, y};
}

optional<Coord> fold_one_vert(const Coord coord, const int v) {
    const auto [x, y] = coord;
    if (y == v) return nullopt;
    if (y < v) return coord;

    const auto dy = y - v;
    return pair{x, v - dy};
}

optional<Coord> fold_one(const Coord coord, const pair<Dir, int> f) {
    const auto [d, v] = f;
    return d == Dir::VERT ? fold_one_vert(coord, v) : fold_one_horz(coord, v);
}

set<Coord> fold_plane(const set<Coord> &ps, const pair<Dir, int> f) {
    set<Coord> result;

    for (const auto p : ps) {
        const auto p_ = fold_one(p, f);
        if (!p_) continue;
        result.insert(*p_);
    }

    return result;
}

vector<string> print_raster(const set<Coord> &ps) {
    vector<string> result(40, string(80, ' '));
    for (const auto [ro, co] : ps) {
        result[ro][co + 10] = '#';
    }
    return result;
}

int main() {
    set<Coord> ps;
    vector<pair<Dir, int>> folds;

    for (string line; getline(cin, line);) {
        if (line == "") continue;

        if (line.find("fold") == 0) {
            const auto parts = split("=", line);
            folds.emplace_back(parts[0].back() == 'x' ? Dir::HORZ : Dir::VERT,
                               stoi(parts[1]));
            continue;
        }

        const auto xy = split(",", line);
        ps.emplace(stoi(xy[0]), stoi(xy[1]));
    }

    for (const auto f : folds) {
        ps = fold_plane(ps, f);
    }

    for (const auto &row : print_raster(ps)) {
        cout << row << '\n';
    }

    return 0;
}
