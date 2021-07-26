#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Coord = complex<int>;
constexpr int row(const Coord coord) { return coord.real(); }
constexpr int col(const Coord coord) { return coord.imag(); }
enum class Cov { NONE, X, H, V };

using CovRowsConcat = vector<Cov>;
using CovRows = vector<vector<Cov>>;

CovRows delinerize(const int h, const int w, const CovRowsConcat &xs) {
    CovRows ans(h, vector<Cov>(w, Cov::NONE));
    for (int ro = 0; ro < h; ++ro) {
        for (int co = 0; co < w; ++co) {
            ans[ro][co] = xs[w * ro + co];
        }
    }
    return ans;
}

vector<CovRowsConcat> all_b_type_layouts(const int h, const int w,
                                         const int b) {
    vector<CovRowsConcat> ans;

    CovRowsConcat curr(h * w, Cov::NONE);
    for (int i = 0; i < b; ++i) curr[i] = Cov::X;
    sort(begin(curr), end(curr));

    do {
        ans.push_back(curr);
    } while (next_permutation(begin(curr), end(curr)));

    return ans;
}

constexpr Coord following(const int w, const Coord crd) {
    return col(crd) < w - 1 ? Coord{row(crd), col(crd) + 1}
                            : Coord{row(crd) + 1, 0};
}

int backtrack_a_type_fills(const CovRows &rows, const Coord crd, const int a) {
    const int h = sz(rows);
    const int w = sz(rows[0]);

    const auto [ro, co] = pair{row(crd), col(crd)};
    if (crd == Coord{h - 1, w - 1} && rows[ro][co] != Cov::NONE) return 1;

    if (rows[ro][co] == Cov::NONE && a) {
        int ans = 0;

        if (co < w - 1 && rows[ro][co + 1] == Cov::NONE) {
            CovRows rows_ = rows;
            rows_[ro][co] = Cov::H;
            rows_[ro][co + 1] = Cov::H;
            ans += backtrack_a_type_fills(rows_, following(w, crd), a - 1);
        }

        if (ro < h - 1 && rows[ro + 1][co] == Cov::NONE) {
            CovRows rows_ = rows;
            rows_[ro][co] = Cov::V;
            rows_[ro + 1][co] = Cov::V;
            ans += backtrack_a_type_fills(rows_, following(w, crd), a - 1);
        }

        return ans;
    }

    return backtrack_a_type_fills(rows, following(w, crd), a);
}

int ways_num(const int h, const int w, const int a, const int b) {
    int ans = 0;

    for (const auto &la : all_b_type_layouts(h, w, b)) {
        const auto rows = delinerize(h, w, la);
        ans += backtrack_a_type_fills(rows, {0, 0}, a);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int h, w, a, b;
    cin >> h >> w >> a >> b;

    cout << ways_num(h, w, a, b) << '\n';
    return 0;
}
