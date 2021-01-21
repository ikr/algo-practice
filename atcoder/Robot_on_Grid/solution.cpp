#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;
using mint = atcoder::modint998244353;

ostream &operator<<(ostream &os, const mint &x) {
    os << x.val();
    return os;
}

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

int count_ways(const vector<string> &rows) {
    const int H = rows.size();
    const int W = rows[0].size();

    vector<vector<mint>> dp(H, vector<mint>(W, 0));
    dp[0][0] = 1;

    cout << dp << '\n';

    return dp.back().back().val();
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
