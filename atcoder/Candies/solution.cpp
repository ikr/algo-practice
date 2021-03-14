#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using mint = atcoder::modint1000000007;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ostream &operator<<(ostream &os, const mint &x) {
    os << x.val();
    return os;
}

mint ways_num(const int k, const vi &xs) {
    vector<vector<mint>> dp(k + 1, vector<mint>(sz(xs), 0));
    vector<vector<mint>> ss(k + 1, vector<mint>(sz(xs), 0));

    for (int child = 0; child < sz(xs); ++child) {
        dp[0][child] = 1;
        ss[0][child] = 1;
    }

    for (int candy = 1; candy <= k; ++candy) {
        dp[candy][0] = candy <= xs[0] ? 1 : 0;
        ss[candy][0] = ss[candy - 1][0] + dp[candy][0];
    }

    const auto dp_range_sum = [&](const int child, const int lo, const int hi) {
        return ss[hi][child] - (lo ? ss[lo - 1][child] : 0);
    };

    for (int child = 1; child < sz(xs); ++child) {
        for (int candy = 1; candy <= k; ++candy) {
            dp[candy][child] =
                dp_range_sum(child - 1, max(0, candy - xs[child]), candy);

            ss[candy][child] = ss[candy - 1][child] + dp[candy][child];
        }
    }

    return dp.back().back();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(9) << fixed;

    int n, k;
    cin >> n >> k;

    vi xs(n);
    for (auto &x : xs) cin >> x;

    cout << ways_num(k, xs) << '\n';
    return 0;
}
