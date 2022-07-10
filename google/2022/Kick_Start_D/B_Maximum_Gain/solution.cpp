#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<ll> best_sum_by_num_taken(const vector<ll> &xs, const int K) {
    const auto n = sz(xs);
    vector<ll> ss(n);
    partial_sum(cbegin(xs), cend(xs), begin(ss));

    const auto sum_between = [&ss](const int i, const int j) -> ll {
        return ss[j] - (i ? ss[i - 1] : 0LL);
    };

    vector<ll> dp(K + 1, 0);

    for (int p = 0; p <= K; ++p) {
        for (int q = 0; q <= K; ++q) {
            if (p + q > K) break;

            if (p - 1 < n && n - q >= 0 && p - 1 < n - q) {
                const auto head = p ? sum_between(0, p - 1) : 0LL;
                const auto tail = q ? sum_between(n - q, n - 1) : 0LL;
                dp[p + q] = max(dp[p + q], head + tail);
            }
        }
    }

    return dp;
}

ll solve(const vector<ll> &A, const vector<ll> &B, const int K) {
    const auto dpa = best_sum_by_num_taken(A, K);
    const auto dpb = best_sum_by_num_taken(B, K);
    ll result{};

    for (int a = 0; a <= K; ++a) {
        const auto b = K - a;
        result = max(result, dpa[a] + dpb[b]);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<ll> A(N);
        for (auto &a : A) cin >> a;

        int M;
        cin >> M;
        vector<ll> B(M);
        for (auto &b : B) cin >> b;

        int K;
        cin >> K;

        cout << "Case #" << i << ": " << solve(A, B, K) << '\n';
    }

    return 0;
}
