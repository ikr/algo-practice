#include <bits/stdc++.h>
using namespace std;
constexpr int M = 1e9 + 7;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

int solve(const int s) {
    if (s < 3) return 0;

    // number of sequences [whose sum is i]
    vector<int> dp(s + 1, 0);
    dp[0] = 1;
    dp[3] = 1;

    for (int i = 4; i <= s; ++i) {
        for (int j = 3; j <= s; ++j) {
            if (i - j >= 0) {
                dp[i] += dp[i - j];
                dp[i] %= M;
            }
        }
    }

    return dp[s];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int s;
    cin >> s;
    cout << solve(s) << '\n';

    return 0;
}
