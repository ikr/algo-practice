#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool confirm_consequtive(const vi &xs) {
    return adjacent_find(cbegin(xs), cend(xs), [](const int a, const int b) {
               return (b - a) != 1;
           }) == cend(xs);
}

optional<int> index_of_mod7(const int v, const vi &xs) {
    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] % 7 == v) return i;
    }

    return nullopt;
}

bool is_part(const vvi &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    if (!confirm_consequtive(grid[0])) return false;

    const auto im0 = index_of_mod7(0, grid[0]);
    if (im0 && *im0 != W - 1) return false;

    const auto im1 = index_of_mod7(1, grid[0]);
    if (im1 && *im1 != 0) return false;

    for (int ro = 1; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (grid[ro][co] != grid[ro - 1][co] + 7) return false;
        }
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int H, W;
    cin >> H >> W;

    vvi grid(H, vi(W, 0));
    for (auto &row : grid) {
        for (auto &x : row) {
            cin >> x;
        }
    }

    const auto ans = is_part(grid);
    cout << (ans ? "Yes" : "No") << '\n';
    return 0;
}
