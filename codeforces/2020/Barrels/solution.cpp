#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll best_diff(vector<int> &xs, const int k) {
    sort(rbegin(xs), rend(xs));
    const ll s =
        accumulate(cbegin(xs) + 1, cbegin(xs) + k + 1, 0LL, plus<ll>{});
    return xs[0] + s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> xs(n, 0);
        for (auto &x : xs) cin >> x;

        cout << best_diff(xs, k) << '\n';
    }

    return 0;
}
