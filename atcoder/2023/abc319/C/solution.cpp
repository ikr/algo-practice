#include <bits/stdc++.h>
using namespace std;

using Grid = array<array<int, 3>, 3>;
using tri = tuple<int, int, int>;

static const set<tri> LineIds{{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6},
                              {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr int in_grid(const Grid &g, const int id) {
    const auto ro = id / 3;
    const auto co = id % 3;
    return g[ro][co];
}

constexpr bool are_disappointing(const int a, const int b, const int c) {
    return (a == b && b != c);
}

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<array<T, N>, N> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
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
        total = total + 1.0;

        for (int i = 2; i < sz(ids); ++i) {
            const auto [ida, idb, idc] = tri{ids[i - 2], ids[i - 1], ids[i]};
            if (!LineIds.contains({ida, idb, idc}) &&
                !LineIds.contains({idc, idb, ida})) {
                continue;
            }

            if (are_disappointing(in_grid(grid, ida), in_grid(grid, idb),
                                  in_grid(grid, idc))) {
                disap = disap + 1.0;
                break;
            }
        }

    } while (next_permutation(begin(ids), end(ids)));

    cout << (1.0 - disap / total) << '\n';
    return 0;
}
