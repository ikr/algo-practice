#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll best_end_sum(const vector<ll> &xs, const int K) {
    vector<ll> ss(sz(xs));
    partial_sum(cbegin(xs), cend(xs), begin(ss));

    ll ans{};

    for (int pre = 0; pre <= K; ++pre) {
        const auto suf = K - pre;

        ll cur = ss.back();

        if (pre) {
            cur -= ss[2 * pre - 1];
        }

        if (suf) {
            cur -= (ss.back() - ss[sz(xs) - suf - 1]);
        }

        ans = max(ans, cur);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, k;
    cin >> n >> k;

    vector<ll> xs(n);
    for (auto &x : xs) cin >> x;
    sort(begin(xs), end(xs));

    cout << best_end_sum(xs, k) << '\n';
    return 0;
}
