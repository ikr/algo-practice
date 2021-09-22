#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int INF = 1e9;

int min_lunchboxes(const pii XY, const vector<pii> &ab) {
    const auto [X, Y] = XY;

    // D[i][j][k] is min boxes up to box i, in order to get exactly min(j, X)
    // of A & min(k, Y) of B
    vector<vvi> D(sz(ab) + 1, vvi(X + 1, vi(Y + 1, INF)));
    D[0][0][0] = 0;

    for (int i = 0; i < sz(ab); ++i) {
        D[i + 1] = D[i];
        const auto [a, b] = ab[i];

        for (int j = 0; j <= X; ++j) {
            for (int k = 0; k <= Y; ++k) {
                auto &curr = D[i + 1][min(j + a, X)][min(k + b, Y)];
                curr = min(curr, D[i][j][k] + 1);
            }
        }
    }

    return D.back()[X][Y];
}

int min_lunchboxes_2(const pii XY, const vector<pii> &ab) {
    const auto [X, Y] = XY;

    // D[i][j][k] is min boxes up to box i, in order to get exactly min(j, X)
    // of A & min(k, Y) of B
    vector<vvi> D(sz(ab), vvi(X + 1, vi(Y + 1, INF)));
    D[0][0][0] = 0;

    const auto [a0, b0] = ab[0];
    D[0][min(a0, X)][min(b0, Y)] = 1;

    for (int i = 1; i < sz(ab); ++i) {
        const auto [a, b] = ab[i];

        for (int j = 0; j <= X; ++j) {
            for (int k = 0; k <= Y; ++k) {
                D[i][j][k] = min(D[i - 1][j][k],
                                 D[i - 1][max(j - a, 0)][max(k - b, 0)] + 1);
            }
        }
    }

    return D.back()[X][Y];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    int X, Y;
    cin >> X >> Y;

    vector<pii> ab(N);
    for (auto &[a, b] : ab) {
        cin >> a >> b;
    }

    assert(min_lunchboxes({X, Y}, ab) == min_lunchboxes_2({X, Y}, ab));

    const auto ans = min_lunchboxes_2({X, Y}, ab);
    cout << (ans >= INF ? -1 : ans) << '\n';
    return 0;
}
