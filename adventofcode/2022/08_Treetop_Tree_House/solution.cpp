#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using Grid = vector<vector<int>>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

int scenic_score(const Grid &grid, const pii m) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    const auto in_bounds = [&](const auto ab) -> bool {
        const auto [ro, co] = ab;
        return 0 <= ro && ro < H && 0 <= co && co < W;
    };

    int result{1};

    for (const pii &dir : {pii{-1, 0}, pii{0, 1}, pii{1, 0}, pii{0, -1}}) {
        auto cur = m;
        vector<int> line;

        while (in_bounds(cur + dir)) {
            cur = cur + dir;
            line.push_back(grid[cur.first][cur.second]);
        }

        result *= [&]() -> int {
            if (line.empty()) return 0;
            if (line[0] >= grid[m.first][m.second]) return 1;

            int p{1};
            for (int i = 1; i < sz(line); ++i) {
                if (line[i] < line[i - 1]) break;
                ++p;
            }
            return p;
        }();
    }

    return result;
}

int num_visible(const Grid &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    int result{};

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            result = max(result, scenic_score(grid, {ro, co}));
        }
    }

    return result;
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

int main() {
    Grid grid;

    for (string line; getline(cin, line);) {
        vector<int> row(sz(line));
        transform(cbegin(line), cend(line), begin(row),
                  [](const char x) { return inof(x) - inof('0'); });
        grid.push_back(row);
    }

    cout << num_visible(grid) << '\n';
    return 0;
}
