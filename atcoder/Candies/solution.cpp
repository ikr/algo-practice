#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

using mint = atcoder::modint1000000007;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

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

mint ways_num(const int k, const vi &xs) {
    vector<vector<mint>> dp(k + 1, vector<mint>(sz(xs), 0));
    for (int child = 0; child < sz(xs); ++child) dp[0][child] = 1;

    for (int candy = 1; candy <= min(k, xs[0]); ++candy) {
        dp[candy][0] = 1;
    }

    for (int candy = 1; candy <= k; ++candy) {
        for (int child = 1; child < sz(xs); ++child) {
            for (int mine = 0; mine <= min(candy, xs[child]); ++mine) {
                dp[candy][child] += dp[candy - mine][child - 1];
            }
        }
    }

    cout << dp << '\n';
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
