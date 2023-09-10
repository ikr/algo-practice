#include <bits/stdc++.h>
using namespace std;

using tri = array<int, 3>;
using Grid = array<tri, 3>;

static const vector<tri> LineIds{{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6},
                                 {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

constexpr int in_grid(const Grid &g, const int id) {
    const auto ro = id / 3;
    const auto co = id % 3;
    return g[ro][co];
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
    double disap = 0.0;

    do {
        [&]() -> void {
            for (const auto &line : LineIds) {
                for (int i = 0; i < 3; ++i) {
                    const auto a = line[i];
                    const auto b = line[(i + 1) % 3];
                    const auto c = line[(i + 2) % 3];

                    if (in_grid(grid, b) == in_grid(grid, c) &&
                        ids[b] < ids[a] && ids[c] < ids[a]) {
                        ++disap;
                        return;
                    }
                }
            }
        }();
    } while (next_permutation(begin(ids), end(ids)));

    cout << (362880.0 - disap) / 362880.0 << '\n';
    return 0;
}
