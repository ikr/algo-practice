#include <bits/stdc++.h>
using namespace std;
using ll = long long;

pair<ll, vector<ll>> merge_two(vector<ll> xs, const int i) {
    xs[i] = xs[i] + xs[i + 1];
    xs.erase(cbegin(xs) + i + 1);
    return {xs[i], xs};
}

double recur(const vector<ll> &xs) {
    const int sz = xs.size();
    if (sz == 2) return accumulate(cbegin(xs), cend(xs), 0LL, plus<ll>{});

    double ans = 0;

    for (int i = 0; i < sz - 1; ++i) {
        const auto merged = merge_two(xs, i);
        const auto score = merged.first;
        const auto sub = merged.second;

        ans += (score + recur(sub)) / (sz - 1);
    }

    return ans;
}

double solve(const vector<ll> xs) { return recur(xs); }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(7) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;
        vector<ll> xs(n, 0);
        for (auto &x : xs) cin >> x;

        cout << "Case #" << i << ": " << solve(xs) << '\n';
    }

    return 0;
}
