#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr ll M = 1e9 + 7;

constexpr ll inc_nz(const ll x) { return x == 0LL ? 0LL : x + 1; }

ll solve(const vector<string> &rows) {
    if (rows[0][0] == '#' || rows.back().back() == '#') return 0;

    const int H = rows.size();
    const int W = rows[0].size();

    vector<vector<ll>> horz(H, vector<ll>(W, 0));
    vector<vector<ll>> vert(H, vector<ll>(W, 0));
    vector<vector<ll>> diag(H, vector<ll>(W, 0));

    for (int c = 1; c < W; ++c) {
        horz[0][c] = rows[0][c] == '.' ? horz[0][c - 1] + 1 : 0;
    }

    for (int r = 1; r < H; ++r) {
        vert[r][0] = rows[r][0] == '.' ? vert[r - 1][0] : 0;
    }

    for (int r = 1; r < H; ++r) {
        for (int c = 1; c < W; ++c) {
            if (rows[r][c] == '#') continue;

            diag[r][c] = (r == 1 && c == 1)
                             ? 1
                             : (inc_nz(diag[r - 1][c - 1]) +
                                horz[r - 1][c - 1] + vert[r - 1][c - 1]);

            horz[r][c] =
                diag[r][c - 1] + inc_nz(horz[r][c - 1]) + vert[r][c - 1];

            vert[r][c] =
                diag[r - 1][c] + horz[r - 1][c] + inc_nz(vert[r - 1][c]);

            diag[r][c] %= M;
            horz[r][c] %= M;
            vert[r][c] %= M;
        }
    }

    return (horz.back().back() + vert.back().back() + diag.back().back()) % M;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int H, W;
    cin >> H >> W;
    vector<string> rows(H, string(W, ' '));

    for (auto &row : rows) {
        cin >> row;
    }

    cout << solve(rows) << '\n';
    return 0;
}
