#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using Coord = pair<int, int>;
static constexpr ll Stretch = 1000000;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> transpose(const vector<string> &m) {
    const auto H = sz(m[0]);
    const auto W = sz(m);

    vector<string> ans(H, string(W, '.'));
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            ans[ro][co] = m[co][ro];
        }
    }
    return ans;
}

bool is_empty_row(const string &row) { return ranges::count(row, '#') == 0; }

vector<int> empty_rows_indices(const vector<string> &grid) {
    vector<int> result;
    for (int i = 0; i < sz(grid); ++i) {
        if (is_empty_row(grid[i])) result.push_back(i);
    }
    return result;
}

ll linear_distance(const vector<int> &ei, int a, int b) {
    if (b < a) swap(a, b);
    ll stretched{};
    for (const int i : ei) {
        if (a <= i && i <= b) ++stretched;
    }
    return b - a - stretched + stretched * Stretch;
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) {
        grid.push_back(line);
    }

    const auto eri = empty_rows_indices(grid);
    const auto eci = empty_rows_indices(transpose(grid));

    vector<Coord> galaxies;
    for (int ro = 0; ro < sz(grid); ++ro) {
        for (int co = 0; co < sz(grid[ro]); ++co) {
            if (grid[ro][co] == '#') galaxies.emplace_back(ro, co);
        }
    }

    ll result{};
    for (int i = 0; i < sz(galaxies) - 1; ++i) {
        for (int j = i + 1; j < sz(galaxies); ++j) {
            const auto [a, b] = galaxies[i];
            const auto [c, d] = galaxies[j];
            result += linear_distance(eri, a, c) + linear_distance(eci, b, d);
        }
    }
    cout << result << '\n';
    return 0;
}
