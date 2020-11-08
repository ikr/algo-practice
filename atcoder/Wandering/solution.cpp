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

template <typename T> struct mmax {
    constexpr T operator()(const T &a, const T &b) const {
        return std::max(a, b);
    }
};

ll max_coord(const vector<ll> &xs) {
    const int n = xs.size();

    vector<ll> ss(n, 0);
    partial_sum(cbegin(xs), cend(xs), begin(ss), plus<ll>{});

    vector<ll> ends(n, 0);
    ends[0] = xs[0];
    for (int i = 1; i < n; ++i) {
        ends[i] = ends[i - 1] + ss[i];
    }

    vector<ll> ms(n, 0);
    partial_sum(cbegin(ss), cend(ss), begin(ms), mmax<ll>{});

    vector<ll> dp(n, 0);
    dp[0] = max(0LL, xs[0]);

    for (int i = 1; i < n; ++i) {
        dp[i] = max(dp[i - 1], ends[i - 1] + ms[i]);
    }

    return dp.back();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<ll> xs(n, 0);
    for (auto &x : xs) cin >> x;

    cout << max_coord(xs) << '\n';
    return 0;
}
