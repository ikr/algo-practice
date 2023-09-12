#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using Mint = atcoder::modint1000000007;
using Matrix = vector<vector<Mint>>;
using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

Mint cell_combination(const Matrix &xss, const Matrix &yss, const int ro,
                      const int co) {
    const int n = sz(xss);
    Mint ans;
    for (int i = 0; i < n; ++i) ans += xss[ro][i] * yss[i][co];
    return ans;
}

Matrix operator*(const Matrix &xss, const Matrix &yss) {
    const int n = sz(xss);
    Matrix ans(n, vector<Mint>(n, 0));

    for (int ro = 0; ro < n; ++ro) {
        for (int co = 0; co < n; ++co) {
            ans[ro][co] = cell_combination(xss, yss, ro, co);
        }
    }

    return ans;
}

Matrix pow(const Matrix &xss, const ll exp) {
    if (exp == 1) return xss;
    if (exp % 2LL) return xss * pow(xss, exp - 1LL);

    const auto q = pow(xss, exp / 2LL);
    return q * q;
}

int k_long_paths_num(const ll k, const Matrix &adj) {
    const auto m = pow(adj, k);

    return accumulate(cbegin(m), cend(m), Mint{0},
                      [](const Mint agg, const vector<Mint> &xs) {
                          return agg +
                                 accumulate(cbegin(xs), cend(xs), Mint{0},
                                            [](const Mint x, const Mint y) {
                                                return x + y;
                                            });
                      })
        .val();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    ll k;
    cin >> k;

    Matrix adj(n, vector<Mint>(n));
    for (auto &row : adj) {
        for (auto &cell : row) {
            int x;
            cin >> x;
            cell = x;
        }
    }

    cout << k_long_paths_num(k, adj) << '\n';
    return 0;
}
