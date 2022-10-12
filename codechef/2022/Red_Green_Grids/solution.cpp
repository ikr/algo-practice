// https://github.com/atcoder/ac-library/blob/master/atcoder/modint.hpp
#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint998244353;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<vector<mint>> combinations(const int n, const int k) {
    assert(k <= n);
    vector<vector<mint>> ans(n + 1, vector<mint>(k + 1, 1));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= min(i, k); ++j) {
            ans[i][j] = i == j ? 1 : ans[i - 1][j - 1] + ans[i - 1][j];
        }
    }

    return ans;
}

vector<vector<mint>> valid_paths_num() {
    const int N = 1000;
    const int M = 1000;

    vector<vector<mint>> D(N, vector<mint>(M, 1));
    for (int ro = 1; ro < N; ++ro) {
        for (int co = 1; co < M; ++co) {
            D[ro][co] = D[ro - 1][co] + D[ro][co - 1];
        }
    }
    return D;
}

mint sum_of_scores(const vector<vector<mint>> &nck,
                   const vector<vector<mint>> &pnum, const int N, const int M) {
    if (N == 1 && M == 1) return 0;
    if ((N + M - 1) % 2) return 0;

    return pnum[N - 1][M - 1] * nck[N + M - 1][(N + M - 1) / 2];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    const auto nck = combinations(1999, 999);
    const auto pnum = valid_paths_num();

    int t;
    cin >> t;
    while (t--) {
        int N, M;
        cin >> N >> M;

        cout << sum_of_scores(nck, pnum, N, M).val() << '\n';
    }

    return 0;
}
