#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr ll M = 998244353LL;

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

ll count_ways(const vector<string> &rows) {
    const int H = rows.size();
    const int W = rows[0].size();

    vector<vector<ll>> dp(H, vector<ll>(W, 0));
    dp[0][0] = 1;

    for (int co = 1; co < W; ++co) {
        switch (rows[0][co - 1]) {
        case 'D':
            dp[0][co] = 0;
            break;

        case 'R':
        case 'X':
            dp[0][co] = dp[0][co - 1];
            break;

        case ' ':
            dp[0][co] = (2 * dp[0][co - 1]) % M;
            break;
        }
    }

    for (int ro = 1; ro < H; ++ro) {
        switch (rows[ro - 1][0]) {
        case 'R':
            dp[ro][0] = 0;
            break;

        case 'D':
        case 'X':
            dp[ro][0] = dp[ro - 1][0];
            break;

        case ' ':
            dp[ro][0] = (2 * dp[ro - 1][0]) % M;
            break;
        }
    }

    for (int ro = 1; ro < H; ++ro) {
        for (int co = 1; co < W; ++co) {
            const char l = rows[ro][co - 1];
            const char u = rows[ro - 1][co];

            ll lw = 0;
            switch (l) {
            case 'D':
                lw = 0;
                break;

            case 'R':
            case 'X':
                lw = dp[ro][co - 1];
                break;

            case ' ':
                lw = (2 * dp[ro][co - 1]) % M;
                break;
            }

            ll uw = 0;
            switch (u) {
            case 'R':
                uw = 0;
                break;

            case 'D':
            case 'X':
                uw = dp[ro - 1][co];
                break;

            case ' ':
                uw = (2 * dp[ro - 1][co]) % M;
                break;
            }
        }
    }

    cout << dp << '\n';

    return dp.back().back();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int H, W, K;
    cin >> H >> W >> K;

    vector<string> rows(H, string(W, ' '));

    while (K--) {
        int ro, co;
        char c;
        cin >> ro >> co >> c;
        rows[ro - 1][co - 1] = c;
    }

    cout << count_ways(rows) << '\n';
    return 0;
}
