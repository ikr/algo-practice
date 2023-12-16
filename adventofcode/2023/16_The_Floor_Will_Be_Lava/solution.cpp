#include <bits/stdc++.h>
using namespace std;

ostream &operator<<(ostream &os, const vector<string> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
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

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

using Coord = pair<int, int>;

enum class Dir { Up, Right, Down, Left };
static constexpr array Delta{Coord{-1, 0}, Coord{0, 1}, Coord{1, 0},
                             Coord{0, -1}};

constexpr Dir dir_of(const Coord delta) {
    const int i = static_cast<int>(ranges::find(Delta, delta) - cbegin(Delta));
    assert(0 <= 1 && i < ssize(Delta));
    return static_cast<Dir>(i);
}

constexpr Coord delta_of(const Dir dir) {
    const int i = static_cast<int>(dir);
    assert(0 <= i && i < ssize(Delta));
    return Delta[i];
}

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

Dir hit_slash(const Dir dir) {
    switch (dir) {
    case Dir::Up:
        return Dir::Right;
    case Dir::Right:
        return Dir::Up;
    case Dir::Down:
        return Dir::Left;
    default:
        assert(dir == Dir::Left);
        return Dir::Down;
    }
}

Dir hit_backslash(const Dir dir) {
    switch (dir) {
    case Dir::Up:
        return Dir::Left;
    case Dir::Right:
        return Dir::Down;
    case Dir::Down:
        return Dir::Right;
    default:
        assert(dir == Dir::Left);
        return Dir::Up;
    }
}

vector<Dir> hit_pipe(const Dir dir) {
    switch (dir) {
    case Dir::Up:
        return {Dir::Up};
    case Dir::Right:
        return {Dir::Up, Dir::Down};
    case Dir::Down:
        return {Dir::Down};
    default:
        assert(dir == Dir::Left);
        return {Dir::Up, Dir::Down};
    }
}

vector<Dir> hit_dash(const Dir dir) {
    switch (dir) {
    case Dir::Up:
        return {Dir::Right, Dir::Left};
    case Dir::Right:
        return {Dir::Right};
    case Dir::Down:
        return {Dir::Right, Dir::Left};
    default:
        assert(dir == Dir::Left);
        return {Dir::Left};
    }
}

vector<Dir> hit(const Dir dir, const char cell) {
    switch (cell) {
    case '/':
        return {hit_slash(dir)};
    case '\\':
        return {hit_backslash(dir)};
    case '|':
        return hit_pipe(dir);
    case '-':
        return hit_dash(dir);
    default:
        assert(cell == '.');
        return {dir};
    }
}

using Beam = pair<Coord, Dir>;

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) grid.push_back(line);
    cerr << grid << endl;

    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    const auto in_bounds = [=](const Coord roco) {
        const auto [r, c] = roco;
        return 0 <= r && r < H && 0 <= c && c < W;
    };

    vector<vector<int>> space(H, vector(W, 0));
    queue<Beam> q;
    q.emplace(Coord{0, -1}, Dir::Right);

    while (!empty(q)) {
        const auto [u, dir] = q.front();
        q.pop();

        const auto dst = u + delta_of(dir);
        if (!in_bounds(dst)) continue;

        const auto [r, c] = dst;
        if (space[r][c] & (1 << inof(dir))) continue;
        space[r][c] |= 1 << inof(dir);

        for (const auto v : hit(dir, grid[r][c])) q.emplace(dst, v);
    }
    cerr << space << endl;

    int result{};
    for (const auto &row : space) {
        for (const auto cell : row) {
            result += (cell != 0);
        }
    }
    cout << result << endl;
    return 0;
}
