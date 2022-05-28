#include <atcoder/modint>
#include <iostream>
#include <vector>
using namespace std;

using mint = atcoder::modint998244353;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

mint solve(const int N, const int M, const int K) {
    // dp(i, j) is the number of sequences of length i, ending with j
    vector<vector<mint>> dp(N + 1, vector<mint>(M + 1, 0));

    for (int j = 1; j <= M; ++j) {
        dp[1][j] = 1;
    }

    for (int i = 2; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            for (int k = K; k <= M; ++k) {
                if (j - k < 1 && j + k > M) break;

                if (j - k >= 0) {
                    dp[i][j] += dp[i - 1][j - k];
                }

                if (j + k != j - k && j + k <= M) {
                    dp[i][j] += dp[i - 1][j + k];
                }
            }
        }
    }

    mint result{};

    for (const auto x : dp.back()) {
        result += x;
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M, K;
    cin >> N >> M >> K;

    cout << solve(N, M, K).val() << '\n';
    return 0;
}
