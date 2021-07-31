#include <atcoder/modint>
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

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Mint = atcoder::modint998244353;
using Matrix = vector<vector<Mint>>;

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

int k_days_roundtrips(const int k, const Matrix &adj) {
    const auto m = pow(adj, k);
    return m[0][0].val();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m, k;
    cin >> n >> m >> k;

    Matrix adj(n, vector<Mint>(n, 1));

    for (int i = 0; i < n; ++i) {
        adj[i][i] = 0;
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        adj[u][v] = 0;
        adj[v][u] = 0;
    }

    cout << k_days_roundtrips(k, adj) << '\n';
    return 0;
}
