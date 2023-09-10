#include <bits/stdc++.h>
using namespace std;

using Grid = array<array<int, 3>, 3>;
using tri = tuple<int, int, int>;

static const set<tri> LineIds{{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6},
                              {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

constexpr int in_grid(const Grid &g, const int id) {
    const auto ro = id / 3;
    const auto co = id % 3;
    return g[ro][co];
}

constexpr bool are_disappointing(const int a, const int b, const int c) {
    return (a == b && b != c) || (b == c && b != a);
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
    double disap = 0;

    do {
        Grid g;

        for (int i = 0; i < 9; ++i) {
            const auto ro = i / 3;
            const auto co = i % 3;
            g[ro][co] = in_grid(grid, ids[i]);
        }

        for (const auto &[a, b, c] : LineIds) {
            if (are_disappointing(in_grid(g, a), in_grid(g, b),
                                  in_grid(g, c))) {
                ++disap;
                break;
            }
        }
    } while (next_permutation(begin(ids), end(ids)));

    cout << (362880.0 - disap) / 362880.0 << '\n';
    return 0;
}
