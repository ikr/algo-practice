#include <bits/stdc++.h>
using namespace std;

using Roco = pair<int, int>;

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

int main() {
    vector<string> grid;
    Roco src{-1, -1};
    Roco dst{-1, -1};
    for (string line; getline(cin, line);) {
        grid.push_back(line);
        if (sz(grid) == 1) src = {0, inof(line.find('.'))};
    }

    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    dst = {H - 1, inof(grid.back().find('.'))};

    cerr << src << " -> " << dst << endl;

    int result{};

    const auto recur = [&](const auto self, vector<vector<bool>> &visited,
                           const Roco p) -> void {
        assert(visited[p.first][p.second]);
        if (p == dst) {
            const auto potential =
                transform_reduce(cbegin(visited), cend(visited), 0, plus<int>{},
                                 [](const auto &row) {
                                     return count(cbegin(row), cend(row), true);
                                 });
            if (potential > result) {
                cerr << "New record: " << potential << endl;
                result = potential;
            }
            return;
        }

        for (const auto &delta : Delta) {
            const auto q = p + delta;
            if (q.first < 0 || q.first >= H) continue;
            if (grid[q.first][q.second] == '#' || visited[q.first][q.second]) {
                continue;
            }
            visited[q.first][q.second] = true;
            self(self, visited, q);
            visited[q.first][q.second] = false;
        }
    };

    vector<vector<bool>> visited(H, vector<bool>(W, false));
    visited[src.first][src.second] = true;
    recur(recur, visited, src);

    cout << (result - 1) << '\n';
    return 0;
}
