#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

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

    // tbl[i][j][k] is min boxes up to index i, in order to get exactly the
    // min(j, X) of A & the min(k, Y) of B
    vector<vvi> tbl(sz(ab), vvi(X + 1, vi(Y + 1, INF)));

    const auto [a0, b0] = ab[0];
    tbl[0][0][0] = 0;
    tbl[0][min(a0, X)][min(b0, Y)] = 1;

    for (int i = 1; i < sz(ab); ++i) {
        tbl[i][0][0] = 0;
        const auto [a, b] = ab[i];

        for (int j = 1; j <= X; ++j) {
            for (int k = 1; k <= Y; ++k) {
                tbl[i][j][k] = min(tbl[i][j][k], tbl[i - 1][j][k]);

                tbl[i][j][k] = min(
                    tbl[i][j][k], tbl[i - 1][max(0, j - a)][max(0, k - b)] + 1);
            }
        }
    }

    return tbl.back()[X][Y];
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

    const auto ans = min_lunchboxes({X, Y}, ab);
    cout << (ans >= INF ? -1 : ans) << '\n';
    return 0;
}
