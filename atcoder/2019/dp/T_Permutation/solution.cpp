#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint1000000007;

struct mplus final {
    mint operator()(const mint a, const mint b) const { return a + b; }
};

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

unsigned int permutations_num(const string &s) {
    const int n = sz(s) + 1;
    // dp[i][j] is the answer for the i different numbers in the first i places,
    // so that the number at the last place is j
    vector<vector<mint>> dp(n + 1, vector<mint>(n + 1, 0));
    dp[1][1] = 1;

    vector<mint> ss(n + 1, 0);

    for (int i = 2; i <= n; ++i) {
        const bool asc = (s[i - 2] == '<');
        partial_sum(cbegin(dp[i - 1]), cbegin(dp[i - 1]) + i, begin(ss),
                    mplus{});

        for (int j = 1; j <= i; ++j) {
            if (asc) {
                dp[i][j] += ss[j - 1];
            } else {
                dp[i][j] += ss[i - 1] - ss[j - 1];
            }
        }
    }

    return accumulate(cbegin(dp.back()), cend(dp.back()), mint{0}, mplus{})
        .val();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    string s(n, ' ');
    cin >> s;

    cout << permutations_num(s) << '\n';
    return 0;
}
