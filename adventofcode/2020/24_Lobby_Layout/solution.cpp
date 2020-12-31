#include <bits/stdc++.h>
using namespace std;
using Coord = tuple<int, int, int>;

template <typename T>
constexpr tuple<T, T, T> operator+(const tuple<T, T, T> &lhs,
                                   const tuple<T, T, T> &rhs) {
    const auto [a, b, c] = lhs;
    const auto [x, y, z] = rhs;
    return {a + x, b + y, c + z};
}

enum class Dir { SE, SW, NE, NW, E, W };

bool is_one_of(const set<string> &xs, const string &x) { return xs.count(x); }

Dir parse_code(const string &code) {
    const map<string, Dir> m{{"se", Dir::SE}, {"sw", Dir::SW}, {"ne", Dir::NE},
                             {"nw", Dir::NW}, {"e", Dir::E},   {"w", Dir::W}};
    return m.at(code);
}

vector<Dir> parse_line(const string &s) {
    const int n = s.size();
    vector<Dir> ans;

    for (int i = 0; i < n; ++i) {
        if (i < n - 1 && is_one_of({"se", "sw", "ne", "nw"}, s.substr(i, 2))) {
            ans.push_back(parse_code(s.substr(i, 2)));
            ++i;
            continue;
        }

        if (s[i] == 'e') {
            ans.push_back(Dir::E);
        } else if (s[i] == 'w') {
            ans.push_back(Dir::W);
        } else {
            assert(false && "parse_line");
        }
    }

    return ans;
}

vector<Coord> dirs_to_deltas(const vector<Dir> &dirs) {
    const map<Dir, Coord> deltas_by_dir{
        {Dir::SE, {0, -1, 1}}, {Dir::SW, {-1, 0, 1}}, {Dir::NE, {1, 0, -1}},
        {Dir::NW, {0, 1, -1}}, {Dir::E, {1, -1, 0}},  {Dir::W, {-1, 1, 0}}};

    vector<Coord> deltas(dirs.size());
    transform(
        cbegin(dirs), cend(dirs), begin(deltas),
        [&deltas_by_dir](const Dir &dir) { return deltas_by_dir.at(dir); });
    return deltas;
}

Coord follow_path(const Coord &origin, const vector<Coord> &deltas) {
    auto ans = origin;
    for (const auto &d : deltas) ans = ans + d;
    return ans;
}

set<Coord> initial_generation(const vector<string> &lines) {
    set<Coord> black;

    for (const auto &line : lines) {
        const auto p = follow_path({0, 0, 0}, dirs_to_deltas(parse_line(line)));
        if (black.count(p)) {
            black.erase(p);
        } else {
            black.insert(p);
        }
    }

    return black;
}

vector<Coord> neigh_deltas() {
    return {{0, -1, 1}, {-1, 0, 1}, {1, 0, -1},
            {0, 1, -1}, {1, -1, 0}, {-1, 1, 0}};
}

vector<Coord> neighs(const Coord &x) {
    const auto ds = neigh_deltas();
    vector<Coord> ans(ds.size());
    transform(cbegin(ds), cend(ds), begin(ans),
              [&x](const auto &d) { return x + d; });
    return ans;
}

int count_neighs(const set<Coord> &black, const Coord &x) {
    const auto ns = neighs(x);
    return count_if(cbegin(ns), cend(ns),
                    [&black](const auto &n) { return black.count(n); });
}

set<Coord> next_generation(const set<Coord> &black) {
    set<Coord> ans = black;

    for (const auto &b : black) {
        const auto ns = neighs(b);
        ans.insert(cbegin(ns), cend(ns));
    }

    for (auto it = cbegin(ans); it != cend(ans);) {
        const auto nc = count_neighs(black, *it);

        if (black.count(*it)) {
            if (nc == 0 || nc > 2) {
                it = ans.erase(it);
            } else {
                ++it;
            }
        } else {
            if (nc == 2) {
                ++it;
            } else {
                it = ans.erase(it);
            }
        }
    }

    return ans;
}

int solve(const vector<string> &lines) {
    auto g = initial_generation(lines);
    for (int i = 0; i < 100; ++i) {
        g = next_generation(g);
    }
    return g.size();
}

int main() {
    vector<string> lines;
    for (string line; getline(cin, line);) lines.push_back(line);
    cout << solve(lines) << '\n';
    return 0;
}
