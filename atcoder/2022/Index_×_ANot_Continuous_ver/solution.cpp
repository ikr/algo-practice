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
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

using ll = long long;

constexpr ll INF = 1e18;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_value(const vector<ll> &xs, const int M) {
    const auto N = sz(xs);
    assert(M <= N);

    vector<ll> ss(N, 0);
    partial_sum(cbegin(xs), cend(xs), begin(ss));

    // dp[i][j] is the max value up to index i on sub-sequences of length j
    vector<vector<ll>> dp(N, vector(M + 1, -INF));
    for (int i = 0; i < N; ++i) dp[i][0] = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 1; j <= M && i - j + 1 >= 0; ++j) {
            dp[i][j] = dp[i][j - 1] + j * xs[i];

            for (int k = 0; k < i && k - j + 1 >= 0; ++k) {
                dp[i][j] = max(dp[i][j], dp[k][j]);
            }
        }
    }

    cerr << dp << endl;

    return dp.back().back();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<ll> xs(N);
    for (auto &x : xs) cin >> x;

    cout << max_value(xs, M) << '\n';
    return 0;
}
