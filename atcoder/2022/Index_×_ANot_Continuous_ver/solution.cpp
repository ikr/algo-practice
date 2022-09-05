#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll INF = 1e18;

ll max_value(const vector<int> &xs, const int M) {
    const auto N = static_cast<int>(xs.size());

    // D[i][j] — max sought value up to index i on sub-sequences of length j
    vector<vector<ll>> D(N, vector(M + 1, -INF));

    // S[i][j] — sum of elements of xs on which the D[i][j] value is reached
    vector<vector<ll>> S(N, vector(M + 1, 0LL));

    vector<ll> D_hi(M + 1, -INF);
    D_hi[1] = xs[0];

    for (int i = 0; i < N; ++i) {
        D[i][0] = 0;
        D[i][1] = xs[i];
        S[i][1] = xs[i];
    }

    for (int i = 1; i < N; ++i) {
        for (int j = 1; j <= M && i + 1 - j >= 0; ++j) {
            const auto o1 = D[i - 1][j - 1] + 1LL * j * xs[i];
            const auto o2 = j <= i + 1 ? D_hi[j] : -INF;

            if (o1 > o2) {
                D[i][j] = o1;
                S[i][j] = S[i - 1][j - 1] + xs[i];
            } else {
                D[i][j] = o2;
                S[i][j] = S[i - 1][j];
            }

            if (j <= i + 1) D_hi[j] = max(D_hi[j], D[i][j]);
        }
    }

    return D.back().back();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    cout << max_value(xs, M) << '\n';
    return 0;
}
