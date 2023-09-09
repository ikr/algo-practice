#include <bits/stdc++.h>
using namespace std;

using Grid = array<array<int, 3>, 3>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr int in_grid(const Grid &g, const int id) {
    const auto ro = id / 3;
    const auto co = id % 3;
    return g[ro][co];
}

array<int, 9> seen(const Grid &g, const array<int, 9> &ids) {
    array<int, 9> ans{};
    transform(cbegin(ids), cend(ids), begin(ans),
              [&](const int id) { return in_grid(g, id); });
    return ans;
}

bool is_disappointing(const array<int, 9> &xs) {
    for (int i = 2; i < sz(xs); ++i) {
        if (xs[i - 2] == xs[i - 1] && xs[i - 1] != xs[i]) return true;
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    Grid grid;
    for (auto &row : grid) {
        for (auto &x : row) cin >> x;
    }

    array<int, 9> ids{0, 1, 2, 3, 4, 5, 6, 7, 8};
    double total = 0;
    double disap = 0;

    do {
        ++total;
        if (is_disappointing(seen(grid, ids))) ++disap;
    } while (next_permutation(begin(ids), end(ids)));

    cout << (1.0 - disap / total) << '\n';
    return 0;
}
