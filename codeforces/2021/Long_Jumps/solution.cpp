#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

ll max_score(const vector<ll> &xs) {
    const int n = xs.size();
    vector<ll> dp(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        const int j = i - 1;
        const ll k = xs[j] + i;

        if (k <= n) {
            dp[k] = max(dp[k], dp[i] + xs[j]);
        } else {
            dp[i] += xs[j];
        }
    }

    return *max_element(cbegin(dp), cend(dp));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<ll> xs(n);
        for (auto &x : xs) cin >> x;

        cout << max_score(xs) << '\n';
    }

    return 0;
}
