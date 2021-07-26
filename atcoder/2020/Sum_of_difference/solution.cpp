#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll sum_of_abs_diffs(const vector<ll> &xs) {
    const ll n = xs.size();
    vector<ll> ss(n + 1, 0);
    partial_sum(cbegin(xs), cend(xs), next(begin(ss)));

    ll ans = 0LL;

    for (ll i = 0LL; i < n; ++i) {
        if (i < n - 1) ans += ss[n] - ss[i + 1] - xs[i] * (n - i - 1);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<ll> xs(n, 0);
    for (auto &x : xs) cin >> x;
    sort(begin(xs), end(xs));

    cout << sum_of_abs_diffs(xs) << '\n';
    return 0;
}
