#include <atcoder/modint>
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

using mint = atcoder::modint1000000007;

ostream &operator<<(ostream &os, const mint &x) {
    os << x.val();
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

unsigned int permutations_num(const string &s) {
    const int n = sz(s);
    // dp[i][j] is the answer for the first i places so that the number at the
    // last place is j
    vector<vector<mint>> dp(n + 1, vector<mint>(n + 1, 0));
    for (int j = 1; j <= n; ++j) {
        dp[1][j] = 1;
    }

    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            const bool asc = s[i - 2] == '<';

            if (asc) {
                for (int k = 1; k < j; ++k) {
                    dp[i][j] += dp[i - 1][k];
                }
            } else {
                for (int k = j + 1; k <= n; ++k) {
                    dp[i][j] += dp[i - 1][k];
                }
            }
        }
    }

    // cerr << dp << endl;

    return accumulate(cbegin(dp.back()), cend(dp.back()), mint{0},
                      [](const mint agg, const mint x) { return agg + x; })
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
