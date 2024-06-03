#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<vector<int>> transpose(const vector<vector<int>> &grid) {
    vector<vector<int>> result(sz(grid[0]), vector(sz(grid), 0));

    for (int ro = 0; ro < sz(grid); ++ro) {
        for (int co = 0; co < sz(grid[0]); ++co) {
            result[co][ro] = grid[ro][co];
        }
    }

    return result;
}

vector<vector<int>> sort_by_first_row(const vector<vector<int>> &grid) {
    const auto w = sz(grid[0]);
    vector<int> idx(w);
    iota(begin(idx), end(idx), 0);

    sort(begin(idx), end(idx),
         [&](const int i, const int j) { return grid[0][i] < grid[0][j]; });

    auto result = grid;
    for (auto &row : result) {
        vector<int> xs(sz(row), 0);
        for (int i = 0; i < sz(xs); ++i) {
            xs[i] = row[idx[i]];
        }
        row = xs;
    }
    return result;
}

vector<pii> coord_index(const vector<vector<int>> &grid) {
    const auto h = sz(grid);
    const auto w = sz(grid[0]);
    vector<pii> result(h * w);
    for (int r = 0; r < h; ++r) {
        for (int c = 0; c < w; ++c) {
            result[grid[r][c]] = {r, c};
        }
    }
    return result;
}

constexpr int mdiff(const int m, const int a, const int b) {
    return ((a - b) + m) % m;
}

bool are_isomorphic(const vector<vector<int>> &A,
                    const vector<vector<int>> &B) {
    const auto h = sz(A);
    const auto w = sz(A[0]);
    if (h == 1 || w == 1) return true;

    const auto iA = coord_index(A);
    const auto iB = coord_index(B);

    vector<pii> ds(sz(iA));
    for (int i = 0; i < sz(iA); ++i) {
        const auto [ra, ca] = iA[i];
        const auto [rb, cb] = iB[i];
        ds[i] = pii{mdiff(h, ra, rb), mdiff(w, ca, cb)};
    }
    if (all_of(cbegin(ds), cend(ds),
               [&](const auto p) { return p == ds[0]; })) {
        return true;
    };

    if (sort_by_first_row(A) == sort_by_first_row(B)) return true;

    if (sort_by_first_row(transpose(A)) == sort_by_first_row(transpose(B))) {
        return true;
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int h, w;
        cin >> h >> w;

        vector<vector<int>> A(h, vector(w, 0));
        for (auto &ra : A) {
            for (auto &a : ra) {
                cin >> a;
                --a;
            }
        }

        vector<vector<int>> B(h, vector(w, 0));
        for (auto &rb : B) {
            for (auto &b : rb) {
                cin >> b;
                --b;
            }
        }

        cout << (are_isomorphic(A, B) ? "YES" : "NO") << '\n';
    }

    return 0;
}
