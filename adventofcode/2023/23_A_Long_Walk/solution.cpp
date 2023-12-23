#include <bits/stdc++.h>
using namespace std;

using Roco = pair<int, int>;

enum class Dir { Up, Right, Down, Left };
static constexpr array Delta{Roco{-1, 0}, Roco{0, 1}, Roco{1, 0}, Roco{0, -1}};

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

constexpr Dir dir_of(const Roco delta) {
    const int i = static_cast<int>(ranges::find(Delta, delta) - cbegin(Delta));
    assert(0 <= 1 && i < ssize(Delta));
    return static_cast<Dir>(i);
}

int main() {
    vector<string> grid;
    Roco src{-1, -1};
    Roco dst{-1, -1};
    for (string line; getline(cin, line);) {
        grid.push_back(line);
        if (sz(grid) == 1) src = {0, inof(line.find('.'))};
    }

    const auto H = sz(grid);
    dst = {H - 1, inof(grid.back().find('.'))};

    cerr << src << " -> " << dst << endl;

    const auto adjacent = [&](const Roco p) {
        vector<Roco> ans;
        for (const auto &delta : Delta) {
            const auto q = p + delta;
            if (q.first < 0 || q.first >= H) continue;
            const auto cell = grid[q.first][q.second];

            if (cell == '#') continue;

            const auto dir = dir_of(delta);
            if (cell == '>' && dir != Dir::Right) continue;
            if (cell == 'v' && dir != Dir::Down) continue;
            if (cell == '<' && dir != Dir::Left) continue;
            if (cell == '^' && dir != Dir::Up) continue;

            ans.push_back(q);
        }
        return ans;
    };

    int result{};
    const auto recur = [&](const auto self, set<Roco> &visited,
                           const Roco p) -> void {
        assert(visited.contains(p));
        if (p == dst) {
            result = max(result, sz(visited));
            return;
        }

        for (const auto &q : adjacent(p)) {
            if (visited.contains(q)) continue;
            visited.insert(q);
            self(self, visited, q);
            visited.erase(q);
        }
        visited.erase(p);
    };

    set<Roco> visited{src};
    recur(recur, visited, src);

    cout << (result - 1) << '\n';
    return 0;
}
