#include <atcoder/modint>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

using mint = atcoder::modint998244353;

mint mint_plus(const mint a, const mint b) { return a + b; }

mint solve(const int N, const int M, const int K) {
    // At step i, dp(j) is the number of sequences of length i, ending with j
    vector<mint> dp(M + 1, 1);
    dp[0] = 0;

    for (int i = 2; i <= N; ++i) {
        vector<mint> ss(M + 1, 0);
        partial_sum(cbegin(dp), cend(dp), begin(ss), mint_plus);

        const auto sum_up = [&ss](const int a, const int b) -> mint {
            assert(a > 0);
            return ss[b] - ss[a - 1];
        };

        vector<mint> dp_(M + 1, 0);
        for (int j = 1; j <= M; ++j) {
            if (!K) {
                dp_[j] = ss.back();
                continue;
            }

            if (j - K >= 1) {
                dp_[j] += sum_up(1, j - K);
            }

            if (j + K <= M) {
                dp_[j] += sum_up(j + K, M);
            }
        }

        swap(dp, dp_);
        assert(dp[0] == mint{0});
    }

    return accumulate(cbegin(dp), cend(dp), mint{0}, mint_plus);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M, K;
    cin >> N >> M >> K;

    cout << solve(N, M, K).val() << '\n';
    return 0;
}
