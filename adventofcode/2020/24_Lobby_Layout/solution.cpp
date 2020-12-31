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

int solve(const vector<string> &lines) {
    return initial_generation(lines).size();
}

int main() {
    vector<string> lines;
    for (string line; getline(cin, line);) lines.push_back(line);
    cout << solve(lines) << '\n';
    return 0;
}
