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

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_coins(const string &xs) {
    const auto n = sz(xs);
    vector<int> dp(n, -1);
    dp[0] = 0;

    const auto is_good = [&](const int i) -> int {
        return i >= 0 && xs[i] != '*';
    };

    for (int i = 1; i < n; ++i) {
        switch (xs[i]) {
        case '.':
            for (const auto j : {i - 2, i - 1}) {
                if (is_good(j)) {
                    dp[i] = max(dp[i], dp[j]);
                }
            }
            break;
        case '@':
            for (const auto j : {i - 2, i - 1}) {
                if (is_good(j)) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            break;
        default:
            assert(xs[i] == '*');
            dp[i] = -1;
        }
    }
    // cerr << dp << endl;
    return *max_element(cbegin(dp), cend(dp));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string xs;
        cin >> xs;
        assert(sz(xs) == n);
        cout << max_coins(xs) << '\n';
    }

    return 0;
}
