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

using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr ll INF = 1e15;

int max_drinks(const vll &xs) {
    // health [at index i] [after j potions drunk]
    vvll dp(sz(xs), vll(sz(xs) + 1, -INF));

    dp[0][0] = 0;
    if (xs[0] >= 0) dp[0][1] = xs[0];

    for (int i = 1; i < sz(xs); ++i) {
        dp[i][0] = 0;

        for (int j = 1; j <= i + 1; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (dp[i][j - 1] + xs[i] >= 0) dp[i][j] = dp[i][j - 1] + xs[i];
        }
    }

    cerr << dp << endl;

    int ans = 0;

    for (int i = 0; i < sz(xs); ++i) {
        for (int j = 1; j <= i + 1; ++j) {
            if (dp[i][j] >= 0) ans = max(ans, j);
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vll xs(n);
    for (auto &x : xs) cin >> x;

    cout << max_drinks(xs) << '\n';
    return 0;
}
