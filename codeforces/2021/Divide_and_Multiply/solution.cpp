#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

ll max_end_sum(vll xs) {
    ll m = 1;

    for (auto &x : xs) {
        while (x % 2 == 0) {
            m *= 2;
            x /= 2;
        }
    }

    const auto it = max_element(begin(xs), end(xs));
    *it *= m;
    return accumulate(cbegin(xs), cend(xs), 0LL);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vll xs(n);
        for (auto &x : xs) cin >> x;

        cout << max_end_sum(move(xs)) << '\n';
    }

    return 0;
}
