#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll min_dist(const vector<int> &xs) {
    const int n = xs.size();
    if (n == 1) return 0;
    const int mid = xs[n / 2];

    ll ans = 0;
    for (const auto x : xs) {
        ans += abs(x - mid);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> xs(n, 0);
    for (auto &x : xs) cin >> x;

    sort(begin(xs), end(xs));
    cout << min_dist(xs) << '\n';

    return 0;
}
